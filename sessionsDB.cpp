#include "sessionsDB.h"
#include "session.h"
using namespace std;

int sessionCounter = 0;

unordered_map<int, void*> sessionMap;

Session* makeSession(int sd)
{
   Session* newSession = new Session(sd, sessionCounter++);
   sessionMap.insert({newSession->getSessionID(), newSession});
   return newSession;
}

bool removeSession(int sessionID) { return sessionMap.erase(sessionID) == 1; }

Session* getSession(int sessionID)
{
   auto session = sessionMap.find(sessionID);
   if (session == sessionMap.end())
      return nullptr;
   return (Session*)session->second;
}