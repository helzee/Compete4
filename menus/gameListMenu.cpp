#include "gameListMenu.h"
#include "../constants.h"
#include "../gameSessionDB.h"
#include "../session.h"
#include "menu.h"

using namespace std;

GameListMenu::GameListMenu()
{
   header = "List of available games:\n------------------------";
   type = GAMELIST;
}

int GameListMenu::joinCommand(CommandTok* comm, Session* session) const
{
   return session->joinGame(comm);
}

int GameListMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
}
