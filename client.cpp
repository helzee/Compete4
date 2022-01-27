/** @file client.cpp
 * @authors Josh Helzerman, Alex Lambert, Joseph Collora
 */

#include "constants.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
   const char *serverName = DEFAULT_SERVER;
   const char *serverPort = DEFAULT_PORT;
   
   switch(argc) {
      
      case 3:
         serverPort = argv[2];
         
      case 2:
         serverName = argv[1];
         break;
      default:
         cerr << "Invalid argument count. Requires at most 2 args: "
              << "(serverName, ServerPort)" << endl
              << "Deafault args are csslab7.uwb.edu and 13337 respectively." 
              << endl;
         return -1;
   }



}