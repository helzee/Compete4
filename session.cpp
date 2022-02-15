#include "session.h"

Session::Session(int clientSd, int sessionID)
{
   this->clientSd = clientSd;
   this->sessionID = sessionID;
}

int Session::getSessionID() { return sessionID; }