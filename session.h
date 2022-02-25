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

using namespace std;

/**
 * @brief Tracks each client's session. takes command tokens and interfaces with menus using those tokens
 * 
 */
class Session
{
public:
   void close();
   bool changeMenu(MenuType menu);
   Session(int, int, const MenuManager*, RecordDB*);
   int getSessionID() const;
   int handleCommand(CommandTok* comm);
   void setMenu(const Menu* menu);
   bool isMenuLocked() const;
   int send(string msg) const;
   Record* getRecord() const;
   const Menu* getMenu() const;
   string getUserName() const;
   bool signin(string password);
   bool isUsernameValid(string username) const;
   bool checkIfRecord(string username) const; //synchronized read of recordDB
   bool isPasswordValid(string password) const;
   bool makeRecord(string user);
   void setPossibleUsername(string username);

private:
   bool menuLocked;
   int sessionID;
   const MenuManager* menuManager; // const access by all sessions
   string username;
   string possibleUsername; 
   const Menu* currMenu; // const access by all sessions
   int clientSd;
   Record* record; // 1 to 1 access
   GameSession* currGame; // synchronized access (2 sessions)
   RecordDB* recordDB; // synchronized access (all sessions)

};

#endif