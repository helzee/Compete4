// Client serves as just that, a client, that is responsible for sending and 
// recieving messages from the server. Messages/commands sent to the server
// follow our HTTP-Like network protocol that uses ASCII.

#include "constants.h"
#include "globalFuncs.h"

using namespace std;

// Declarations for helper functions
// -----------------------------------------------------------------------------
// Establishes a connection to the server using network sockets
int establishConnection(const char* serverName, const char* serverPort);

// Allows for a multi-threaded client that enables simultaneous sending and
// recieving from the game server. Full definition above method.
void* serverListen(void* ptr);

// Quick use function that enables quick error throwing
void throwError(const char* message, int value);

// Contains socket descriptor
struct thread_data {
   int sd;
};

/**
 * @brief Main function of the client, parses the arguments passed at compile 
 * (server port and name/IP), establishes a connection using the helper. If 
 * no port is specified by client, the connection is made on default port.
 * 
 * @param argc count of arguments, should be 3 - 1
 * @param argv arguments, argument1 = name, argument2 = port
 * @return int 
 */
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
      throwError("Thread Creation Error", iret);
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
         send(readBuf, clientSd);
   }

   pthread_exit(NULL);
   close(clientSd);
   exit(EXIT_SUCCESS);
}

/**
 * @brief Thread for the client meant for listening for messages from the server
 * handles the exit conditions for the program within it's listen loop.
 * 
 * @param ptr pointer to the socket descriptor "data"
 * @return void* 
 */
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

/**
 * @brief Using the arguments passed to the client (parsed in main) and subsequently 
 * to this method, establish a TCP connection to the gameserver and return the socket 
 * descriptor to main. The sd will then be used to recieve and send messages to the 
 * connect4 game-server.
 * 
 * @param serverName argv defined servername/IP
 * @param serverPort argv defined serverport
 * @return int socket descriptor
 */
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
      cerr << "getaddrinfo() error : " << gai_strerror(error) << endl;
      exit(EXIT_FAILURE);
   }

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

/**
 * @brief Helper method that quickly allows us to throw errors to the user and 
 * gracefully terminate the client application.
 * 
 * @param message specified error message to send
 * @param value value associated with error message
 */
void throwError(const char* message, int value)
{
   cerr << message << " : " << value << endl;
   exit(EXIT_FAILURE);
}