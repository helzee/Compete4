#include "session.h"
#include "commandLexer.h"
#include "menus/menu.h"
#include "menus/menuManager.h"
#include "userRecord.h"
#include "userRecordDB.h"

/**
 * @brief Construct a new Session:: Session object
 *
 * @param clientSd
 * @param sessionID
 */

Session::Session(int clientSd, int sessionID, const MenuManager* menuManager,
                 RecordDB* recordDB)
{
   menuLocked = false;
   this->clientSd = clientSd;
   this->sessionID = sessionID;
   this->menuManager = menuManager;
   currMenu = menuManager->getMenu(MAIN);
   username = "";
   record = nullptr;
   this->recordDB = recordDB;
}

const Menu* Session::getMenu() const { return currMenu; }

bool Session::changeMenu(MenuType menu)
{
   if (!isMenuLocked()) {
      currMenu = menuManager->getMenu(menu);
      return true;
   }
   return false;
}

string Session::getUserName() const { return username; }

int Session::getSessionID() const { return sessionID; }

/**
 * @brief tells the menu to interpret a command token
 *
 * @param comm
 * @return int
 */
int Session::handleCommand(CommandTok* comm)
{

   return currMenu->navigate(comm, this);
}

void Session::setMenu(const Menu* menu) { currMenu = menu; }

bool Session::isMenuLocked() const { return menuLocked; }

int Session::send(string message) const
{
   while (write(clientSd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;

   return 0;
}

bool Session::signin(string password)
{
   Record* record = recordDB->getRecord(username, password);
   if (record != nullptr) {
      this->record = record;
      this->username = username;
      return true;
   }
   return false;
}

Record* Session::getRecord() const { return record; }

bool Session::isUsernameValid(string username) const {
   Record::isUsernameValid(username);
}
bool Session::checkIfRecord(string username) const {
   recordDB->checkIfRecord(username);
}
