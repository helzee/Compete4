/** @file server.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"

using namespace std;

// Declarations
void* runClientSession(void* ptr);


struct thread_data {
   
   int sd;         // socket number
};


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

   struct addrinfo hints, *res;
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_UNSPEC;     // either v4 or v6
   hints.ai_socktype = SOCK_STREAM; // use TCP
   hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

   // update res. check t his return value!
   int error = getaddrinfo(NULL, serverPort, &hints, &res);
   if (error != 0) {
      cerr << "getaddrinfo() Error! " << gai_strerror(error) << endl;
      return -1;
   }

   // make a socket, bind it, and listen to it
   int serverSd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
   if (serverSd == -1) {
      cerr << "Socket creation error!" << errno << endl;
      freeaddrinfo(res);
      return -1;
   }

   // lose the pesky "Address already in use" error message
   const int yes = 1;
   error =
       setsockopt(serverSd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
   if (error == -1) {
      cerr << "Set Socket Option Error!" << endl;
      close(serverSd);
      freeaddrinfo(res);
      return -1;
   }

   // bind the socket
   error = bind(serverSd, res->ai_addr, res->ai_addrlen);
   if (error < 0) {
      cerr << "Binding issue. " << errno << endl;
      close(serverSd);
      freeaddrinfo(res);
      return -1;
   }

   // listen to up to n connection requests
   error = listen(serverSd, BACKLOG);
   if (error < 0) {
      cerr << "Listen issue. " << errno << endl;
      close(serverSd);
      freeaddrinfo(res);
      return -1;
   }

   // accept incoming connections
   struct sockaddr_storage clientAddr;
   socklen_t clientAddrSize = sizeof(clientAddr);
   while (1) {
      // accept and create a new socket for communication newSd
      int newSd =
          accept(serverSd, (struct sockaddr*)&clientAddr, &clientAddrSize);
      if (newSd == -1) {
         cerr << "socket connection error!" << errno << endl;
         close(serverSd);
         freeaddrinfo(res);
         return -1;
      }
      // create a new thread
      pthread_t newThread;
      struct thread_data* data = new thread_data;
      
      data->sd = newSd;
      int iret1 =
          pthread_create(&newThread, NULL, runClientSession, (void*)data);
      if (iret1 != 0) {
         cerr << "Thread creations error: " << iret1 << endl;
         close(newSd);
      }
   }
}

void* runClientSession(void* ptr) {
   char rcvBuffer[MAX_MSG_SIZE];
   char sendBuffer[MAX_MSG_SIZE];
   while (1)
   {
      // receive data from client
      thread_data* data = (thread_data*)ptr;
      int nRead = 0;
      while (nRead < MAX_MSG_SIZE) {
         nRead += read(data->sd, rcvBuffer, MAX_MSG_SIZE - nRead);
      }
      cout << rcvBuffer; //test info

      //determine message from client
      

      //send return msg to client
   }

   return ptr;
}