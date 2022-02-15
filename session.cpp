
#include "session.h"

Session::Session(int sd, int id)
{
   clientSd = sd;
   currMenu = 0;
   currGameID = 0;
   sessionID = id;

   // don't care about initial value of session ID, just assign this value and
   // allow other classes to use next ones
   // sessionID = ++sessionCounter;
}

int Session::getSessionID() { return sessionID; }


