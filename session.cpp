#include "session.h"
#include "constants.h"

Session::Session()
{
   currMenu = 0;
   currGameID = 0;
   
   // don't care about initial value of session ID, just assign this value and
   // allow other classes to use next ones
   sessionID = ++sessionCounter;
}

int Session::getSessionID() { return sessionID; }

int Session::getNewSessionID() { return sessionCounter++; }
