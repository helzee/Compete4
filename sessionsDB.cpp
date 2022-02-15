#include "constants.h"
#include "session.cpp"
#include <unordered_map>

using namespace std;

unordered_map<int, Session> sessionMap = new unordered_map<int Session>();

Session* makeSession()
{
   Session* newSession = new Session();
   sessionMap.insert(newSession->getSessionID(), newSession);
   return newSession;
}