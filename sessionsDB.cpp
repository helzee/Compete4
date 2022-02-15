#include "constants.h"
#include "session.cpp"
#include <unordered_map>

using namespace std;

auto sessionMap = new unordered_map<int, Session*>();

Session* makeSession()
{
   Session* newSession = new Session();
   sessionMap.insert(newSession->getSessionID(), newSession);
   return newSession;
}

bool removeSession(int sessionID) { sessionMap.erase(sessionID) == 1; }

Session* getSession(int sessionID)
{
   auto session = sessionMap.find(sessionID);
   if (session == sessionMap.end())
      return nullptr;
   return &session;
}