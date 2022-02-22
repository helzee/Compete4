#include "session.h"
#include "commandLexer.h"
#include "menus/menu.h"

/**
 * @brief Construct a new Session:: Session object
 *
 * @param clientSd
 * @param sessionID
 */

Session::Session(int clientSd, int sessionID)
{
   menuLocked = false;
   this->clientSd = clientSd;
   this->sessionID = sessionID;
   currMenu = MAIN;
}

Menu* determineMenu(MenuType currMenu) { return allMenus[currMenu]; }

int Session::getSessionID() const { return sessionID; }

/**
 * @brief tells the menu to interpret a command token
 *
 * @param comm
 * @return int
 */
int Session::handleCommand(CommandTok* comm)
{

   return determineMenu(currMenu)->navigate(comm, this);
}

void Session::setMenu(MenuType menu) { currMenu = menu; }

bool Session::isMenuLocked() const { return menuLocked; }

int Session::send(string message) const
{
   while (write(clientSd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;
      
   return 0;
}

Record* Session::getRecord() const { return record; }