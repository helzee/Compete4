#include "constants.h"
#include "session.cpp"

Session* makeSession()
{
   Session* newSession = new Session();
   return newSession;
}