#include "menu.h"
#include "../commandLexer.h"
#include "globalFuncs.h"
#include "session.h"

#include "loginMenu.h"
#include "mainMenu.h"
#include "makeAccMenu.h"
#include "signInMenu.h"

using namespace std;

Menu::Menu()
{
   
   const Menu* makeMenus[] = {new Menu(),
                              (const Menu*)new MainMenu(),
                              (const Menu*)new LoginMenu(),
                              (const Menu*)new SignInMenu(),
                              (const Menu*)new MakeAcctMenu(),
                              (const Menu*)new GuestMenu()};

   allMenus = makeMenus;
   type = MENU;
   header = "DEFAULT HEADER";
}

int Menu::navigate(CommandTok* comm, Session* session)
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

int Menu::sendWelcome(Session* session) const { return sendGlobalHelp(session); }

int Menu::sendGlobalHelp(Session* session) const
{
   send(HELP_TEXT1, session->getSessionID());
   return send(HELP_TEXT2, session->getSessionID());
}
int Menu::sendBadCommand(Session* session) const
{
   return send(BADCOMMAND_TEXT, session->getSessionID());
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
   return send("You cannot go back from here", session->getSessionID());
}
// ---------------------------------------------------------------------------
int Menu::nameCommand(CommandTok* comm, Session* session) const
{
   if (session->record != nullptr) {
      string name = "Your name is " + session->record->getName() + "\n";
      return send(name, session->clientSd);
   } else
      return send("You are not logged in.\n", session->clientSd);
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
   return send(LBOARD_TEXT, session->clientSd);
}
int Menu::mainCommand(CommandTok* comm, Session* session) const {
   
   if (changeMenu(session, MAIN)) {
      allMenus[newMenu]->sendWelcome(session);
      return 0;
   }
   return 1;
}
int Menu::guestCommand(CommandTok* comm, Session* session) const;

bool Menu::changeMenu(Session* session, MenuType menu) const {
   Menu* newMenu = allMenus[menu];
   if (!session->isMenuLocked()) {
      session->setMenu(newMenu);
      newMenu->sendWelcome(session);
      return true;
   } else {
      return send("Cannot leave this menu yet", session->getSessionID);
      return false;
   }
     }