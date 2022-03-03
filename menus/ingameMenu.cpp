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
   return changeMenu(session, MAIN);
}