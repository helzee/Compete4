#include "sessionsDB.h"
#include "constants.h"
#include "menus/menuManager.h"
#include "session.h"
#include "userRecordDB.h"
using namespace std;

SessionDB::SessionDB(const MenuManager* mmanager, RecordDB* recordDB)
{
   menuManager = mmanager;
   this->recordDB = recordDB;
   sessionCounter = 0;
}

void SessionDB::close(Session* session) {
   session->close();
   removeSession(session->getSessionID());
   // flush all records to disk
   recordDB->saveRecordToDisk();
}

Session* SessionDB::makeSession(int sd)
{
   Session* newSession =
       new Session(sd, sessionCounter++, menuManager, recordDB);
   sessionMap.insert({newSession->getSessionID(), newSession});
   return newSession;
}

bool SessionDB::removeSession(int sessionID)
{
   return sessionMap.erase(sessionID) == 1;
}

Session* SessionDB::getSession(int sessionID)
{
   auto session = sessionMap.find(sessionID);
   if (session == sessionMap.end())
      return nullptr;
   return (Session*)session->second;
}