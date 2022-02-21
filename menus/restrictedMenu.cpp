#include "restrictedMenu.h"
#include "menu.h"
#include "../constants.h"
#include "../globalFuncs.h"
#include "../session.h"

RestrictedMenu::RestrictedMenu() { header = "Restricted menu header"; 
}

int RestrictedMenu::badCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}
int RestrictedMenu::helpCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}
int RestrictedMenu::exitCommand(CommandTok* comm, Session* session) const { return -1; }
int RestrictedMenu::printCommand(CommandTok* comm, Session* session) const
{
   // this is the parent menu class. not any specific menu. default print is
   // global
   // help
   return sendWelcome(session);
}
// ---------------------------------------------------------------------------
/**
 * @brief
 *
 * @param comm
 * @param session
 * @return int
 */
int RestrictedMenu::backCommand(CommandTok* comm, Session* session) const
{
   // should be implemented in  ALL child classes. bad command by default
   return send("You cannot go back from here", session->getSessionID());
}
// ---------------------------------------------------------------------------
int RestrictedMenu::nameCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}

// ---------------------------------------------------------------------------
int RestrictedMenu::loginCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}
int RestrictedMenu::signinCommand(CommandTok* comm, Session* session) const
{
return sendWelcome(session);
}
int RestrictedMenu::makeAcctCommand(CommandTok* comm, Session* session) const
{
return sendWelcome(session);
}
int RestrictedMenu::lBoardCommand(CommandTok* comm, Session* session) const
{
return sendWelcome(session);
}
int RestrictedMenu::mainCommand(CommandTok* comm, Session* session) const {
   
   if (changeMenu(session, MAIN)) {
      return 0;
   }
   return 1;
}
int RestrictedMenu::guestCommand(CommandTok* comm, Session* session) const {
   return sendWelcome(session);
}