/** @file session.h
 *
 */

#ifndef SESSION_H
#define SESSION_H

#include "constants.h"

class GameSession;
class Record;
class CommandTok;
class Menu;
class MenuManager;
class RecordDB;
class GameSessionDB;

using namespace std;

/**
 * @brief Tracks each client's session. takes command tokens and interfaces with
 * menus using those tokens
 *
 */
class Session
{
public:
   Session(int, int, const MenuManager*, RecordDB*, GameSessionDB*);
   void close();

   int handleCommand(CommandTok* comm);
   int send(string msg) const;

   bool changeMenu(MenuType menu);
   bool isMenuLocked() const;

   int getSessionID() const;
   Record* getRecord() const;
   const Menu* getMenu() const;
   string getUserName() const;

   bool checkIfRecord(string username) const; // synchronized read of recordDB
   bool makeRecord(string user);
   bool signin(string password);
   bool signinAsGuest();
   bool isUsernameValid(string username);
   bool isPasswordValid(string password) const;
   void setPossibleUsername(string username);
   void setGame(GameSession*);
   int printLeaderboard() const;
   void listGames() const;
   int joinGame(CommandTok*);
   bool dropPiece(CommandTok*);
   int printBoard() const;

private:
   bool menuLocked; // Locks user to stay in current menu
   int sessionID;
   int clientSd; // Socket Description, used to send messages to client

   string username;         // after successful signin, this is set
   string possibleUsername; // Temporary variable used to store a potential
                            // username before proper password is given

   Record* record;                 // 1 to 1 access to store player information
   RecordDB* recordDB;             // synchronized access (all sessions)
   GameSessionDB* gameDB;          // synchronized access (all sessions)
   GameSession* currGame;          // synchronized access (2 sessions)
   const MenuManager* menuManager; // const access by all sessions
   const Menu* currMenu;           // const access by all sessions
};

#endif