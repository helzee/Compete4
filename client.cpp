/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"
#include "globalFuncs.h"

using namespace std;

int establishConnection(const char* serverName, const char* serverPort);

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

   // This is the buffer that will store messages
   // This stores messages to send and recieved messages.
   char sendBuffer[MAX_MSG_SIZE];
   string command, response;

   /** Initialization is completed. Socket is ready to use
    * While loop is used until program termination.
    * The while loop simply sends messages from the server, then
    * receives and displays messages from the server.
    */
   while (1) {
      response = recieve(clientSd);
      cout << response << endl;

      if (fgets(sendBuffer, MAX_MSG_SIZE, stdin) != NULL) {
         command = (string)sendBuffer;
         send(command, clientSd);
      } else {
         command = "print";
         send(command, clientSd);
      }
   }
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
   if (error != 0) {
      cerr << "getaddrinfo() Error! " << gai_strerror(error) << endl;
      exit(EXIT_FAILURE);
   }

   // make a socket
   int clientSd = socket(servInfo->ai_family, servInfo->ai_socktype,
                         servInfo->ai_protocol);
   if (clientSd == -1) {
      cerr << "Socket creation error!" << errno << endl;
      exit(EXIT_FAILURE);
   }
   // lose pesky "Address already in use" error message
   int status = connect(clientSd, servInfo->ai_addr, servInfo->ai_addrlen);
   if (status < 0) {
      cerr << "Failed to connect to the server" << errno << endl;
      exit(EXIT_FAILURE);
   }

   cerr << "Connected!\n";
   return clientSd;
}