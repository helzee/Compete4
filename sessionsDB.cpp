#include "sessionsDB.h"
#include "constants.h"
#include "gameSessionDB.h"
#include "menus/menuManager.h"
#include "session.h"
#include "userRecordDB.h"
using namespace std;

/**
 * @brief Construct a new SessionDB object. This object basically encapsulates
 * all of the server logic. It instantiates the MenuManager, the RecordDB, and
 * the game sessionDB upon construction.
 *
 *
 */
SessionDB::SessionDB()
{
   // initialize menu objects in manager
   menuManager = new MenuManager();

   // initialize record database

   recordDB = new RecordDB();

   // initialize game session DB
   gameSessionDB = new GameSessionDB();

   sessionCounter = 0;
}

void SessionDB::close(Session* session)
{
   session->close();
   removeSession(session->getSessionID());
   // flush all records to disk
   recordDB->saveRecordToDisk();
}

Session* SessionDB::makeSession(int sd)
{
   Session* newSession =
       new Session(sd, sessionCounter++, menuManager, recordDB, gameSessionDB);
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