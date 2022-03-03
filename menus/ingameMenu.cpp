#include "ingameMenu.h"
#include "../constants.h"
#include "../gameSessionDB.h"
#include "../session.h"
#include "menu.h"

using namespace std;

InGameMenu::InGameMenu()
{
   header = "You are currently in a "
            "gamesession\n------------------------------------------------";
   type = INGAME;
}

int InGameMenu::dropPieceCommand(CommandTok* comm, Session* session) const
{
   return session->dropPiece(comm);
}

int InGameMenu::printCommand(CommandTok* comm, Session* session) const
{
   return session->printBoard();
}

int InGameMenu::backCommand(CommandTok* comm, Session* session) const
{
   // Need to update at some point to require confirmation and accept losing
   // game
   return changeMenu(session, MAIN);
}

int InGameMenu::badCommand(CommandTok* comm, Session* session) const
{
   return 0; // return session->sendChat(comm);
}