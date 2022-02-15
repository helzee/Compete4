/** @file session.h
 * 
*/

#pragma once
#include "constants.h"

using namespace std;

class Session {
   public:
      char username[MAX_NAME];
      int currMenu;
      int currGameID;

      Session();
      int getSessionID();

   private:
      int sessionID;
};