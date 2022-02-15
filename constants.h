/** @file constants.h
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <arpa/inet.h> // inet_ntoa
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netdb.h>       // gethostbyname
#include <netinet/in.h>  // htonl, htons, inet_ntoa
#include <netinet/tcp.h> // SO_REUSEADDR
#include <pthread.h>
#include <string>
#include <sys/socket.h> // socket, bind, listen, inet_ntoa
#include <sys/types.h>  // socket, bind
#include <unistd.h>     // read, write, close
#include <unordered_map>

#define DEFAULT_SERVER "csslab7.uwb.edu"
#define DEFAULT_PORT "13337"
#define MAX_MSG_SIZE 128
#define BACKLOG 20

#define MAX_NAME 20

#define ARG_SERV_MESSAGE                                                       \
   "Invalid argument count. Requires at most 1 arg: (ServerPort)\n"            \
   "Default arg is 13337"

#define ARG_CLI_MESSAGE                                                        \
   "Invalid argument count. Requires at most 2 args: (ServerName, "            \
   "ServerPort)\nDefault args are csslab7.uwb.edu and 13337 respectively."

enum MENUS { MAIN, LOGIN, SIGNIN, MAKEACCOUNT, GUEST };

#endif