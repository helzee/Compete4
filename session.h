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

using namespace std;

/**
 * @brief Tracks each client's session. takes command tokens and interfaces with menus using those tokens
 * 
 */
class Session
{
public:
   bool changeMenu(MenuType menu);
   Session(int, int, const MenuManager*);
   int getSessionID() const;
   int handleCommand(CommandTok* comm);
   void setMenu(const Menu* menu);
   bool isMenuLocked() const;
   int send(string msg) const;
   Record* getRecord() const;
   const Menu* getMenu() const;
   string getUserName() const;
   bool signin(string password);

private:
   bool menuLocked;
   int sessionID;
   const MenuManager* menuManager;
   string username;
   const Menu* currMenu;
   int clientSd;
   Record* record = nullptr;
   GameSession* currGame = nullptr;
};

#endif