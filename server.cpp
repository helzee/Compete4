/**
 * @file server.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 * @brief This is the main thread of execution for the serverside of Connect4
 * Online. It initializes a SessionDB object which will act as the manager for
 * all client sessions. The SessionDB object will also act as the initializer
 * and manager of all the peripheral objects that each client will interact
 * with. After these objects are initialized, the server creates a socket, binds
 * it, and listens to the socket. It creates a new thread for each new client
 * that connects to it, and that thread creates a Session instance to handle
 * that client's interactions with the server and other clients connected to the
 * server.
 * @version 0.1
 * @date 2022-02-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "commandParser.h"
#include "constants.h"
#include "gameSession.h"
#include "gameSessionDB.h"
#include "globalFuncs.h"
#include "menus/menuManager.h"
#include "session.h"
#include "sessionsDB.h"
#include "userRecordDB.h"

using namespace std;

// Declarations
void* clientSession(void* ptr);
int establishServer(const char* serverPort);
void throwError(const char* message, int value);
void throwError(const char* message, int value, int serverSd);

struct thread_data {
   int sd; // socket number
   SessionDB* sessionDB;
};

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv)
{
   const char* serverPort = DEFAULT_PORT;
   if (argc == 2)
      serverPort = argv[2];
   else if (argc > 2) {
      cerr << ARG_SERV_MESSAGE << endl;
      exit(EXIT_FAILURE);
   }

   int serverSd = establishServer(serverPort);

   // initialize session database
   SessionDB* sessionDB = new SessionDB();

   // accept incoming connections
   struct sockaddr_storage cliAddr;
   socklen_t cliAddrSize = sizeof(cliAddr);
   int newSd, iret;

   // continuously wait for new connections
   while (1) {

      // accept and create a new socket for communication newSd
      newSd = accept(serverSd, (struct sockaddr*)&cliAddr, &cliAddrSize);
      if (newSd == -1)
         throwError("Socket Connection Error", errno, serverSd);

      // create a new thread to handle this connection
      pthread_t newThread;
      struct thread_data* data = new thread_data;
      data->sd = newSd;
      data->sessionDB = sessionDB;

      iret = pthread_create(&newThread, NULL, clientSession, (void*)data);
      if (iret != 0) {
         cerr << "Thread creations error: " << iret << endl;
         close(newSd);
      }
      cerr << "Connected to Client" << endl;
   }
}

/**
 * @brief
 *
 * @param ptr
 * @return void*
 */
void* clientSession(void* ptr)
{
   thread_data* data = (thread_data*)ptr;
   int sd = data->sd;
   string command;
   SessionDB* sessionDB = data->sessionDB;
   // make a session to handle this connection
   Session* session = sessionDB->makeSession(sd);
   parseCommand("print", session);

   // continuously recieve commands from client until they exit
   while (1) {
      command = receive(sd);

      cerr << "Menu[" << session->getMenu()->getType()
           << "]: Command= " << command << endl;

      // Returns false if the command was exit/quit
      if (parseCommand(command, session) < 0)
         break;
   }

   cerr << "Closing Client Connection" << endl;
   close(sd);
   sessionDB->close(session);
   return nullptr;
}

int establishServer(const char* serverPort)
{
   struct addrinfo hints, *res;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_UNSPEC;     // either v4 or v6
   hints.ai_socktype = SOCK_STREAM; // use TCP
   hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

   // update res. check t his return value!
   int error = getaddrinfo(NULL, serverPort, &hints, &res);
   if (error != 0) {
      cerr << "getaddrinfo() Error : " << gai_strerror(error) << endl;
      exit(EXIT_FAILURE);
   }

   // make a socket, bind it, and listen to it
   int serverSd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
   if (serverSd == -1)
      throwError("Socket Creation Error", errno);

   // lose the pesky "Address already in use" error message
   const int y = 1; // yes
   error = setsockopt(serverSd, SOL_SOCKET, SO_REUSEADDR, (char*)&y, sizeof(y));
   if (error == -1)
      throwError("Set Socket Option Error", error, serverSd);

   // bind the socket
   error = bind(serverSd, res->ai_addr, res->ai_addrlen);
   if (error < 0)
      throwError("Binding Error", errno, serverSd);

   // listen to up to n connection requests
   error = listen(serverSd, BACKLOG);
   if (error < 0)
      throwError("Listen Error", errno, serverSd);

   return serverSd;
}

void throwError(const char* message, int value)
{
   cerr << message << " : " << value << endl;
   exit(EXIT_FAILURE);
}

void throwError(const char* message, int value, int serverSd)
{
   cerr << message << " : " << value << endl;
   close(serverSd);
   exit(EXIT_FAILURE);
}