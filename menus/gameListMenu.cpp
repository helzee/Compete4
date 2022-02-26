#include "gameListMenu.h"
#include "../constants.h"
#include "menu.h"

using namespace std;

GameListMenu::GameListMenu()
{
   header = "List of available games:\n-----------------------";
   type = GAMELIST;
}

int GameListMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
}
