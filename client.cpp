/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"


using namespace std;

int main(int argc, char **argv) {
   const char *serverName = DEFAULT_SERVER;
   const char *serverPort = DEFAULT_PORT;
   
   switch(argc) {
      case 0:
      case 1:
         serverName = argv[1];
      case 2:
         serverPort = argv[2];
      }
}