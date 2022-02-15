/** @file server.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "commandParser.cpp"
#include "constants.h"
#include "sessionsDB.cpp"

using namespace std;

// Declarations
int establishServer(const char* serverName, const char* serverPort);
void throwError(const char* message, int value);
void throwError(const char* message, int value, int serverSd);
void* clientSession(void* ptr);

struct thread_data {
   int sd; // socket number
};

int main(int argc, char** argv)
{
   const char* serverName = DEFAULT_SERVER;
   const char* serverPort = DEFAULT_PORT;

   switch (argc) {
   case 3:
      serverPort = argv[2];
   case 2:
      serverName = argv[1];
   case 1:
      break;
   default:
      cerr << ARG_MESSAGE << endl;
      exit(EXIT_FAILURE);
   }

   int serverSd = establishServer(serverName, serverPort);

   // accept incoming connections
   struct sockaddr_storage cliAddr;
   socklen_t cliAddrSize = sizeof(cliAddr);

   while (1) {

      // accept and create a new socket for communication newSd
      int newSd = accept(serverSd, (struct sockaddr*)&cliAddr, &cliAddrSize);
      if (newSd == -1)
         throwError("Socket Connection Error", errno, serverSd);

      // create a new thread
      pthread_t newThread;
      struct thread_data* data = new thread_data;
      data->sd = newSd;

      int iret = pthread_create(&newThread, NULL, clientSession, (void*)data);
      if (iret != 0) {
         cerr << "Thread creations error: " << iret << endl;
         close(newSd);
      }
   }
}

int establishServer(const char* serverName, const char* serverPort)
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

void* clientSession(void* ptr)
{
   thread_data* data = (thread_data*)ptr;
   char rcvBuffer[MAX_MSG_SIZE];
   char sendBuffer[MAX_MSG_SIZE];

   Session* session = makeSession(data->sd);

   while (1) {
      // receive data from client
      int nRead = 0;
      while (nRead < MAX_MSG_SIZE) {
         nRead += read(data->sd, rcvBuffer, MAX_MSG_SIZE - nRead);
      }
      cout << rcvBuffer; // test info

      //turn buffer into formatted string
      string command(rcvBuffer);

      // determine message from client
      if (parseCommand(command, session)) {

         // send return msg to client
         if (write(data->sd, "Message recieved!\n", MAX_MSG_SIZE) < 0) {
            cerr << "Scenario 3: Problem with write " << errno << endl;
            close(data->sd);
            return ptr;
         }
      } else {
         if (write(data->sd, "Invalid Command\n", MAX_MSG_SIZE) < 0) {
            cerr << "Scenario 3: Problem with write " << errno << endl;
            close(data->sd);
            return ptr;
         }
      }

      return ptr;
   }