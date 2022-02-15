/** @file session.h
 *
 */

#pragma once
#include "constants.h"

using namespace std;

class Session
{
public:
   char username[MAX_NAME];
   int currMenu;
   int currGameID;
   int clientSd;

   Session(int);
   int getSessionID();

private:
   int sessionID;
   static int sessionCounter;
   int getNewSessionID();
};
