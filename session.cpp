#include "session.h"
#include "commandLexer.h"
#include "menus/menu.h"
#include "menus/menuManager.h"

/**
 * @brief Construct a new Session:: Session object
 *
 * @param clientSd
 * @param sessionID
 */


Session::Session(int clientSd, int sessionID, const MenuManager* menuManager)
{
   menuLocked = false;
   this->clientSd = clientSd;
   this->sessionID = sessionID;
   this->menuManager = menuManager;
   currMenu = menuManager->getMenu(MAIN);
}

const Menu* Session::getMenu() const { return currMenu; }

bool Session::changeMenu(MenuType menu) {
   if (!isMenuLocked()) {
      currMenu = menuManager->getMenu(menu);
      return true;
   }
   return false;
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

void Session::setMenu(const Menu* menu) { currMenu = menu; }

bool Session::isMenuLocked() const { return menuLocked; }

int Session::send(string message) const
{
   while (write(clientSd, message.c_str(), MAX_MSG_SIZE) != MAX_MSG_SIZE)
      ;
      
   return 0;
}

Record* Session::getRecord() const { return record; }