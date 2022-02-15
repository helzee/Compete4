/** @file session.h
 * 
*/

#pragma once
#include "constants.h"

using namespace std;

class Session {
   public:
      string username;
      int currMenu;
      int currGameID;

      Session();
      int getSessionID();

   private:
      int sessionID;
      static int sessionCounter;
      int getNewSessionID();
};

