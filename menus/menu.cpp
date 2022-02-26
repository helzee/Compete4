#include "menu.h"
#include "../commandLexer.h"

#include "../session.h"

#include "guestMenu.h"
#include "loginMenu.h"
#include "mainMenu.h"
#include "makeAccMenu.h"
#include "menuManager.h"
#include "signInMenu.h"

using namespace std;

/**
 * @brief Returns the type of menu this instance is
 *
 * @return MenuType this instance's menu type
 */
MenuType Menu::getType() const { return type; }

/**
 * @brief Construct a new Menu:: Menu object
 *
 */
Menu::Menu()
{

   type = MENU;
   header = "DEFAULT HEADER";
}

/**
 * @brief Determines what command function to call based on the command token
 *
 *
 * @param comm command token used to jump to the proper command handling
 * function
 * @param session the session this command was generated by
 * @return int : return == 0 for success, return > 0 for issue but not failure,
 *          return < 0 if exit command.
 */
int Menu::navigate(CommandTok* comm, Session* session) const
{
   TokType menu = comm->getType();
   // switch statement cases occur in order of TokType enum.
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
   case TOKLIST:
      return listCommand(comm, session);
   // insert command functions here
   default:
      return badCommand(comm, session);
   }
}

/**
 * @brief Send this menu's header string to the client
 *
 *
 * @param session the session/client to send to
 * @return int 0 = success, -1 = failure
 */
int Menu::sendWelcome(Session* session) const { return session->send(header); }

/**
 * @brief Send the list of global help commands to the client
 *
 * @param session the session/client to send to
 * @return int 0 = success, -1 = failure
 */
int Menu::sendGlobalHelp(Session* session) const
{
   session->send(HELP_TEXT1);
   return session->send(HELP_TEXT2);
}

/**
 * @brief Tell the client they have send a command that isnt recognized
 * by this menu
 *
 * @param session the session/client to send to
 * @return int 0 = success, -1 = failure
 */
int Menu::sendBadCommand(Session* session) const
{
   return session->send(BADCOMMAND_TEXT);
}

/**
 * @brief Changes they current menu the client is in
 * if the change call to session succeeded, print the
 * new menu's welcome message. Else tell the client they
 * cannot change menus.
 *
 * @param session The session/client to change the menu of
 * @param menu the menu type (enum) we want to change the session to
 * @return int 0 = success, 1 = can't change menu yet
 */
int Menu::changeMenu(Session* session, MenuType menu) const
{

   if (session->changeMenu(menu)) {
      session->getMenu()->sendWelcome(session);
      return 0;
   }
   session->send("Cannot leave this menu yet");
   return 1;
}

// Below this comment are the command functions that may/may not be
// overridden by child classes. You can think of these functions
// as the default commands that a menu can start with.

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
   return sendWelcome(session);
}

int Menu::backCommand(CommandTok* comm, Session* session) const
{
   return session->send("You cannot go back from here");
}

int Menu::nameCommand(CommandTok* comm, Session* session) const
{
   if (session->getRecord() != nullptr) {
      string name = "Your name is " + session->getUserName() + ".";
      return session->send(name);
   } else
      return session->send("You are not logged in.");
}

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

int Menu::listCommand(CommandTok* comm, Session* session) const
{
   if (changeMenu(session, GAMELIST)) {
      return 0;
   }
   return 1;
}
