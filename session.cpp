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
   this->record = nullptr;
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

void Session::close()
{
   // close currGame. opponent wins if unfinished
   // update wins/losses of player

   
}

void Session::setMenu(const Menu* menu) { currMenu = menu; }

bool Session::isMenuLocked() const { return menuLocked; }

int Session::send(string message) const
{
   while (write(clientSd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;

   return 0;
}

void Session::setPossibleUsername(string username)
{
   possibleUsername = username;
}

bool Session::makeRecord(string password)
{
   Record* temp = recordDB->makeRecord(possibleUsername, password);
   if (temp == nullptr) {
      send("Error occured: Could not make account. Please try again.");
      return false;
   }
   this->record = temp;
   username = possibleUsername;
   return true;
}

bool Session::isPasswordValid(string password) const
{
   if (Record::isPasswordValid(password)) {
      return true;
   }
   send("Password must be at least 5 chars long.");
   return false;
}

bool Session::signin(string password)
{
   Record* record = recordDB->getRecord(possibleUsername, password);
   if (record != nullptr) {
      this->record = record;
      this->username = possibleUsername;
      return true;
   }
   return false;
}

Record* Session::getRecord() const { return record; }

bool Session::isUsernameValid(string username)
{
   if (Record::isUsernameValid(username)) {
      possibleUsername = username;
      return true;
   }
   send("Username must be between 4 and 32 characters (inclusive)"
        "and contain no spaces or tabs");
   return false;
}

// check if username exists
bool Session::checkIfRecord(string username) const
{
   return recordDB->checkIfRecord(username);
}
