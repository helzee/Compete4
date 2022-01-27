/** @file constants.h
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
*/

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

#define DEFAULT_SERVER "csslab7.uwb.edu"
#define DEFAULT_PORT "13337"
#define MAX_MSG_SIZE 128
#define BACKLOG 20


