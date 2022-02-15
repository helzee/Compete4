#include "constants.h"
#include "session.h"

int sessionCounter = 0;
int getNewSessionID() { return sessionCounter++; }

Session::Session() { currMenu = 0;
   currGameID = 0;
}

int Session::getSessionID() { return sessionID; }

