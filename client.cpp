/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"

using namespace std;

int main(int argc, char **argv)
{
   const char *serverName = DEFAULT_SERVER;
   const char *serverPort = DEFAULT_PORT;

   switch (argc) {

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
   int status = connect(clientSd, servInfo->ai_addr, servInfo->ai_addrlen);
   if (status < 0) {
      cerr << "Failed to connect to the server" << errno << endl;

      return -1;
   }
   cerr << "Connected!\n";

   // This is the buffer that will store messages
   // This stores messages to send and recieved messages.
   char sendBuffer[MAX_MSG_SIZE];

   /** Initialization is completed. Socket is ready to use
    * While loop is used until program termination.
    * The while loop simply sends messages from the server, then
    * receives and displays messages from the server.
    */
   while (1) {
      if (fgets(sendBuffer, MAX_MSG_SIZE, stdin) != NULL) {
         if (write(clientSd, sendBuffer, MAX_MSG_SIZE) < 0) {
            cerr << "Scenario 3: Problem with write " << errno << endl;
            close(clientSd);
            return -1;
         }
         // flush
         int nRead = 0;
         // change to 1 read call?
         while (nRead < MAX_MSG_SIZE) {
            nRead += read(clientSd, sendBuffer, MAX_MSG_SIZE - nRead);
         }
         cout << sendBuffer; // test info
      }
   }
}
