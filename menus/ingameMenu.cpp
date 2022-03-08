#include "ingameMenu.h"
#include "../constants.h"
#include "../gameSessionDB.h"
#include "../session.h"
#include "menu.h"

using namespace std;

InGameMenu::InGameMenu()
{
   header = "\n------You are now in a Game------\n";
   type = INGAME;
}

int InGameMenu::dropPieceCommand(CommandTok* comm, Session* session) const
{
   return session->dropPiece(comm);
}

int chatCommand(CommandTok* comm, Session* session) const
{
   return session->sendChat(comm);
}

int InGameMenu::printCommand(CommandTok* comm, Session* session) const
{
   return session->printBoard();
}

int GameListMenu::helpCommand(CommandTok* comm, Session* session) const
{
   return session->send(GAME_HELP_TEXT);
}

int InGameMenu::backCommand(CommandTok* comm, Session* session) const
{
   // Need to update at some point to require confirmation and accept losing
   // game
   if (session->allowedToExit)
      return session->changeMenu(session, MAIN);
   else {
      session->askToLeave();
      return 0;
   }
}

int InGameMenu::badCommand(CommandTok* comm, Session* session) const
{
   return 0; // return session->sendChat(comm);
}