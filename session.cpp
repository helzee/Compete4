#include "session.h"
#include "commandLexer.h"
#include "gameSession.h"
#include "gameSessionDB.h"
#include "menus/menu.h"
#include "menus/menuManager.h"
#include "userRecord.h"
#include "userRecordDB.h"

Session::Session(int clientSd, int sessionID, const MenuManager* menuManager,
                 RecordDB* recordDB, GameSessionDB* gameDB)
{

   menuLocked = false;
   allowedToExit = false;
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
      if (currMenu->getType() == INGAME && currGame != nullptr) {
         currGame->disconnectPlayer(this);
      }
      currMenu = menuManager->getMenu(menu);
      allowedToExit = false;
      return true;
   }
   return false;
}

void Session::leaveGame(MenuType menu)
{
   currMenu = menuManager->getMenu(menu);
   currGame = nullptr;
   allowedToExit = false;
}

void Session::askToLeave()
{
   this->send("Are you sure you want to leave? Type your command again "
              "to leave.");
   allowedToExit = true;
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

bool Session::isUsernameInUse(string username)
{
   return recordDB->checkIfInUse(username);
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
int Session::signin(string password)
{
   Record* record = recordDB->getRecord(possibleUsername, password);
   if (record == nullptr)
      return 1;

   if (record->inUse) {
      this->send("Username is in use at the moment. If this is an issue, "
                 "please contact the administators.");
      changeMenu(LOGIN);
      return 2;
   }

   this->record = record;
   this->username = possibleUsername;
   record->inUse = true;
   return 0;
}

bool Session::signinAsGuest()
{
   username = possibleUsername;
   record = new Record(username, 0);
   return true;
}

bool Session::signOut()
{
   if (record == nullptr)
      return false;

   username = "";
   possibleUsername = "";
   record->inUse = false;
   record = nullptr;
   return true;
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

string Session::printStats() const
{
   string buffer;
   buffer = "You have won " + to_string(record->getGamesWon()) +
            " games and lost " + to_string(record->getGamesLost()) +
            " games in total.\nAcross all of your " +
            to_string(record->getGamesPlayed()) +
            " games played, you have a win/loss ratio of " +
            to_string(record->getRatio()) + ".\n";
}

void Session::printLeaderboard() const
{
   string buffer = recordDB->printLeaderboard() + printStats();

   int totalBytesSent = buffer.length();
   for (int i = 0; i < totalBytesSent; i += MAX_MSG_SIZE) {
      this->send(buffer.substr(i, MAX_MSG_SIZE));
   }
}

void Session::listGames() const { this->send(gameDB->gamesList()); }

int Session::createGame()
{
   int newGameIndex = gameDB->makeGame();
   if (newGameIndex == -1)
      return 1;
   if (gameDB->joinGame(newGameIndex, this)) {
      this->changeMenu(INGAME);
      return 0;
   }

   this->send("Failed to join game, try again");
   return 1;
}

int Session::joinGame(CommandTok* comm)
{
   const char* command = comm->getLex().c_str();
   int joinIndex = -1;
   if (command[1] == 'o')
      joinIndex = atoi(command + 5);
   else
      joinIndex = atoi(command + 2);

   if (gameDB->joinGame(joinIndex, this)) {
      this->changeMenu(INGAME);
      return 0;
   }

   this->send("Failed to join game, try again");
   return 1;
}

bool Session::dropPiece(CommandTok* comm)
{
   return currGame->dropPiece(this, stoi(comm->getLex()));
}

int Session::printBoard() const
{
   if (currGame == nullptr)
      return 1;

   this->send(currGame->printBoard());
   return 0;
}

int Session::sendChat(CommandTok* comm)
{
   // if message section of command string is empty, return false
   // "" is not a valid chat to send, check for spaces
   string message = comm->getLex();
   auto regClear = new regex("(>[[:space:]]+)");

   if (!regex_match(message, *regClear)) {
      if (currGame->chat(this, comm->getLex()))
         return 0;
      return 1;
   } else {
      this->send("Empty chat messages or  are not allowed");
      return 1;
   }
}

void Session::updateLB() { recordDB->updateLeaderboard(this); }