#include "session.h"
#include "commandLexer.h"
#include "gameSessionDB.h"
#include "menus/menu.h"
#include "menus/menuManager.h"
#include "userRecord.h"
#include "userRecordDB.h"

Session::Session(int clientSd, int sessionID, const MenuManager* menuManager,
                 RecordDB* recordDB, GameSessionDB* gameDB)
{

   menuLocked = false;
   this->clientSd = clientSd;
   this->sessionID = sessionID;
   this->menuManager = menuManager;
   currMenu = menuManager->getMenu(MAIN);
   username = "";
   possibleUsername = "";
   this->record = nullptr;
   this->recordDB = recordDB;
   this->gameDB = gameDB;
}

void Session::setGame(GameSession* game) { currGame = game; }

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
 * @brief tells the current menu to interpret a command token
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

/**
 * @brief Checks to see if the given password and (previously given) username
 * match a record. If so, that player is "signed in", in other words, the record
 * is pointed to by this session and the possibleUsername (that was stored
 * before pasword validation) is now stored as the actual username of the
 * client.
 *
 * @param password the password the client typed in.
 * @return true if sign in was successful (password matched the one in the
 * record)
 * @return false if signin was unsuccessful (password did not match that on
 * record)
 */
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

int Session::printLeaderboard() const
{
   string buffer = recordDB->printLeaderboard();
   int totalBytesSent = buffer.length();
   for (int i = 0; i < totalBytesSent; i += MAX_MSG_SIZE) {
      this->send(buffer.substr(i, MAX_MSG_SIZE));
   }

   return totalBytesSent;
}

void Session::listGames() const
{
   string buffer = gameDB->gamesList();
   for (int i = 0; i < buffer.length(); i += MAX_MSG_SIZE)
      this->send(buffer.substr(i, MAX_MSG_SIZE));
}

int Session::joinGame(CommandTok* comm)
{
   const char* command = comm->getLex();
   int joinIndex = -1;
   if (command[1] == 'o')
      joinIndex = atoi(command + 5);
   else
      joinIndex = atoi(command + 2);

   if (gameDB->joinGame(joinIndex, this))
      return 0;
   this->send("Failed to join game, try again");
   return 1;
}