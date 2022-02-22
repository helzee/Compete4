/** @file session.h
 *
 */



#ifndef SESSION_H
#define SESSION_H

#include "constants.h"


class GameSession;
class Record;
class CommandTok;


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
   void setMenu(MenuType menu);
   bool isMenuLocked() const;
   int send(string msg) const;
   Record* getRecord() const;

private:
   bool menuLocked;
   int sessionID;

   
   MenuType currMenu;
   int clientSd;
   Record* record = nullptr;
   GameSession* currGame = nullptr;
};

#endif