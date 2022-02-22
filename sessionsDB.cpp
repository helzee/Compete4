#include "sessionsDB.h"
#include "session.h"
#include "menus/menuManager.h"
using namespace std;

int sessionCounter = 0;

unordered_map<int, void*> sessionMap;

Session* makeSession(int sd, const MenuManager* menuManager)
{
   Session* newSession = new Session(sd, sessionCounter++, menuManager);
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