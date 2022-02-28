/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"
#include "globalFuncs.h"

using namespace std;

int establishConnection(const char* serverName, const char* serverPort);
void* serverListen(void* ptr);
void throwError(const char* message, int value);

struct thread_data {
   int sd;
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
      cerr << ARG_CLI_MESSAGE << endl;
      exit(EXIT_FAILURE);
   }

   int clientSd = establishConnection(serverName, serverPort);

   pthread_t listenThread;
   struct thread_data* data = new thread_data;
   data->sd = clientSd;
   int iret = pthread_create(&listenThread, NULL, serverListen, (void*)data);
   if (iret != 0) {
      close(clientSd);
      throwError("Thread Creation Error", iret, clientSd);
   }

   // This is the buffer that will store messages
   // This stores messages to send and recieved messages.
   char readBuf[MAX_MSG_SIZE];

   /** Initialization is completed. Socket is ready to use
    * While loop is used until program termination.
    * The while loop simply sends messages from the server, then
    * receives and displays messages from the server.
    */
   while (1) {
      if (fgets(readBuf, MAX_MSG_SIZE, stdin) != NULL)
         send((string)readBuf, clientSd);
   }

   pthread_exit(NULL);
   close(clientSd);
   exit(EXIT_SUCCESS);
}

void* serverListen(void* ptr)
{
   int clientSd = ((thread_data*)ptr)->sd;
   string response;

   while (true) {
      response = receive(clientSd);
      cout << response << endl;

      if (cmp(response, "exit"))
         break;
   }
   close(clientSd);
   exit(EXIT_SUCCESS);
}

int establishConnection(const char* serverName, const char* serverPort)
{
   // create server info structure
   struct addrinfo hints, *servInfo; // loaded with getaddrinfo()
   memset(&hints, 0, sizeof(hints)); // initialize memory in struct hints
   hints.ai_family = AF_UNSPEC;      // use IPv4 or IPv6
   hints.ai_socktype = SOCK_STREAM;  // use TCP

   // call getaddrinfo() to update servInfo
   int error = getaddrinfo(serverName, serverPort, &hints, &servInfo);
   if (error != 0)
      throwError("getaddrinfo() Error", gai_strerror(error));

   // make a socket
   int clientSd = socket(servInfo->ai_family, servInfo->ai_socktype,
                         servInfo->ai_protocol);
   if (clientSd == -1)
      throwError("Socket creation error!", errno);

   // lose pesky "Address already in use" error message
   int status = connect(clientSd, servInfo->ai_addr, servInfo->ai_addrlen);
   if (status < 0)
      throwError("Failed to connect to the server", errno);

   cerr << "Connected!" << endl;
   return clientSd;
}

void throwError(const char* message, int value)
{
   cerr << message << " : " << value << endl;
   exit(EXIT_FAILURE);
}