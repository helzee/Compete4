#include "session.h"
#include "commandLexer.h"
#include "menus/menu.h"
#include "menus/mainMenu.h"

/**
 * @brief Construct a new Session:: Session object
 *
 * @param clientSd
 * @param sessionID
 */

Session::Session(int clientSd, int sessionID)
{
   menuLocked = false;
   clientSd = clientSd;
   sessionID = sessionID;
   currMenu = mainMenu;
}

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

void Session::setMenu(const Menu* newMenu) { currMenu = newMenu; }

bool Session::isMenuLocked() const { return menuLocked; }

int Session::send(string message) const
{
   while (write(clientSd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;
      
   return 0;
}

Record* Session::getRecord() const { return record; }