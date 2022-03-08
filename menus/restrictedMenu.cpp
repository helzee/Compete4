#include "restrictedMenu.h"
#include "../commandLexer.h"
#include "../constants.h"
#include "../globalFuncs.h"
#include "../session.h"
#include "menu.h"

/**
 * @brief Construct a new Restricted Menu:: Restricted Menu object
 * This menu is not an abstract class, but it is treated like one.
 * It is not added to the menu manager.
 *
 */
RestrictedMenu::RestrictedMenu() { header = "Restricted menu header"; }

// implement different global help commands here?

int RestrictedMenu::badCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}
int RestrictedMenu::helpCommand(CommandTok* comm, Session* session) const
{
   return sendGlobalHelp(session);
}
int RestrictedMenu::exitCommand(CommandTok* comm, Session* session) const
{
   if (!session->allowedToExit)
      return -1;
   else {
      session->askToLeave();
      return 0;
   }
}
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
   return session->send("You cannot go back from here");
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
int RestrictedMenu::mainCommand(CommandTok* comm, Session* session) const
{

   if (changeMenu(session, MAIN)) {
      return 0;
   }
   return 1;
}
int RestrictedMenu::guestCommand(CommandTok* comm, Session* session) const
{
   return sendWelcome(session);
}