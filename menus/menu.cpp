#include "menu.h"
#include "../commandLexer.h"
#include "../globalFuncs.h"
#include "../session.h"
#include "../userRecord.h"

#include "guestMenu.h"
#include "loginMenu.h"
#include "mainMenu.h"
#include "makeAccMenu.h"
#include "menuManager.h"
#include "signInMenu.h"

using namespace std;

MenuType Menu::getType() const { return type; }

Menu::Menu()
{

   type = MENU;
   header = "DEFAULT HEADER";
   // menuManager.addMenu(this, MENU);
}

int Menu::navigate(CommandTok* comm, Session* session) const
{
   TokType menu = comm->getType();
   switch (menu) {
   case TOKBAD:
      return badCommand(comm, session);
   case TOKHELP:
      return helpCommand(comm, session);
   case TOKEXIT:
      return exitCommand(comm, session);
   case TOKPRINT:
      return printCommand(comm, session);
   case TOKBACK:
      return backCommand(comm, session);
   case TOKNAME:
      return nameCommand(comm, session);
   case TOKLOGIN:
      return loginCommand(comm, session);
   case TOKSIGNIN:
      return signinCommand(comm, session);
   case TOKMAKEACCT:
      return makeAcctCommand(comm, session);
   case TOKLBOARD:
      return lBoardCommand(comm, session);
   case TOKMAIN:
      return mainCommand(comm, session);
   case TOKGUEST:
      return guestCommand(comm, session);
   // insert new cases here
   default:
      return badCommand(comm, session);
   }
}

int Menu::sendWelcome(Session* session) const
{
   return sendGlobalHelp(session);
}

int Menu::sendGlobalHelp(Session* session) const
{
   session->send(HELP_TEXT1);
   return session->send(HELP_TEXT2);
}
int Menu::sendBadCommand(Session* session) const
{
   return session->send(BADCOMMAND_TEXT);
}

int Menu::badCommand(CommandTok* comm, Session* session) const
{
   return sendBadCommand(session);
}
int Menu::helpCommand(CommandTok* comm, Session* session) const
{
   return sendGlobalHelp(session);
}
int Menu::exitCommand(CommandTok* comm, Session* session) const { return -1; }
int Menu::printCommand(CommandTok* comm, Session* session) const
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
int Menu::backCommand(CommandTok* comm, Session* session) const
{
   // should be implemented in  ALL child classes. bad command by default
   return session->send("You cannot go back from here");
}
// ---------------------------------------------------------------------------
int Menu::nameCommand(CommandTok* comm, Session* session) const
{
   if (session->getRecord() != nullptr) {
      string name = "Your name is " + session->getRecord()->getName() + "\n";
      return session->send(name);
   } else
      return session->send("You are not logged in.\n");
}

// ---------------------------------------------------------------------------
int Menu::loginCommand(CommandTok* comm, Session* session) const
{
   return sendBadCommand(session);
}
int Menu::signinCommand(CommandTok* comm, Session* session) const
{
   return sendBadCommand(session);
}
int Menu::makeAcctCommand(CommandTok* comm, Session* session) const
{
   return sendBadCommand(session);
}
int Menu::lBoardCommand(CommandTok* comm, Session* session) const
{
   return session->send(LBOARD_TEXT);
}
int Menu::mainCommand(CommandTok* comm, Session* session) const
{

   if (changeMenu(session, MAIN)) {
      return 0;
   }
   return 1;
}
int Menu::guestCommand(CommandTok* comm, Session* session) const
{
   return sendBadCommand(session);
}

int Menu::changeMenu(Session* session, MenuType menu) const
{

   if (session->changeMenu(menu)) {
      session->getMenu()->sendWelcome(session);
      return 0;
   }
   session->send("Cannot leave this menu yet");
   return 1;
}