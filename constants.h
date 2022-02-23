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

// gameSession constants
// ----------------------------------------------------------------------------
#define BOARD_ROW 6
#define BOARD_COL 7
#define MAX_GAMES 10
// ----------------------------------------------------------------------------

#define ARG_SERV_MESSAGE                                                       \
   "Invalid argument count. Requires at most 1 arg: (ServerPort)\n"            \
   "Default arg is 13337"

#define ARG_CLI_MESSAGE                                                        \
   "Invalid argument count. Requires at most 2 args: (ServerName, "            \
   "ServerPort)\nDefault args are csslab7.uwb.edu and 13337 respectively."



// Prime 7879 * Prime 6949 = 54,751,171
#define HASH_NUMBER 54751171

// menu enums. Last enum is not a menu, but is used to keep track of number of menus
enum MenuType { MENU = 0, MAIN, LOGIN, SIGNIN, MAKEACCOUNT, GUEST, PASSWORD, 
MAKEPASSWORD, NUM_OF_MENUS };

class Menu;
class Session;
class CommandTok;
class RestrictedMenu;

#endif