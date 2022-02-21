/** @file session.h
 *
 */



#ifndef SESSION_H
#define SESSION_H

#include "constants.h"

class GameSession;
class Menu;
class Record;


using namespace std;

/**
 * @brief Tracks each client's session. takes command tokens and interfaces with menus using those tokens
 * 
 */
class Session
{
public:
   
   

   Session(int, int);
   int getSessionID() const;
   int handleCommand(CommandTok* comm);
   void setMenu(Menu*);
   bool isMenuLocked() const;

private:
   bool menuLocked;
   int sessionID;
   Menu* currMenu;
   int clientSd;
   Record* record = nullptr;
   GameSession* currGame = nullptr;
};

#endif