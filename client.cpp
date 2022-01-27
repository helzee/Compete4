/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"
#include <cstdio>
#include <iostream>
#include <arpa/inet.h> // inet_ntoa
#include <netdb.h>       // gethostbyname
#include <netinet/in.h>  // htonl, htons, inet_ntoa
#include <netinet/tcp.h> // SO_REUSEADDR
#include <pthread.h>
#include <sys/socket.h> // socket, bind, listen, inet_ntoa
#include <sys/types.h> // socket, bind
#include <unistd.h>    // read, write, close
#include <cstring>

using namespace std;

int main(int argc, char **argv) {
   const char *serverName = DEFAULT_SERVER;
   const char *serverPort = DEFAULT_PORT;
   
   switch(argc) {
      
      case 3:
         serverPort = argv[2];
         
      case 2:
         serverName = argv[1];
         
      case 1:
         break;
      default:
         cerr << "Invalid argument count. Requires at most 2 args: "
              << "(serverName, ServerPort)" << endl
              << "Default args are csslab7.uwb.edu and 13337 respectively." 
              << endl;
         return -1;
   }


   // create server info structure
   struct addrinfo hints, *servInfo; // loaded with getaddrinfo()
   memset(&hints, 0, sizeof(hints)); // initialize memory in struct hints
   hints.ai_family = AF_UNSPEC;      // use IPv4 or IPv6
   hints.ai_socktype = SOCK_STREAM;  // use TCP

   // call getaddrinfo() to update servInfo
   int error = getaddrinfo(serverName, serverPort, &hints, &servInfo);
   if (error != 0) {
      cerr << "getaddrinfo() Error! " << gai_strerror(error) << endl;
      exit(1);
   }

   // make a socket
   int clientSd = socket(servInfo->ai_family, servInfo->ai_socktype,
                         servInfo->ai_protocol);
   if (clientSd == -1) {
      cerr << "Socket creation error!" << errno << endl;

      return -1;
   }
   // lose pesky "Address already in use" error message
   // int status = connect(clientSd, servInfo->ai_addr, servInfo->ai_addrlen);
   // if (status < 0) {
   //    cerr << "Failed to connect to the server" << errno << endl;

   //    return -1;
   // }

   // This is the buffer that will store messages
   // This stores messages to send and recieved messages.
   char sendBuffer[MAX_MSG_SIZE];

   

   /** Initialization is completed. Socket is ready to use
    * While loop is used until program termination.
    * The while loop simply sends messages from the server, then
    * receives and displays messages from the server.
   */
   while(1) {
      if (fgets(sendBuffer, MAX_MSG_SIZE, stdin) != NULL) {
         puts(sendBuffer);
      }
      }
}

