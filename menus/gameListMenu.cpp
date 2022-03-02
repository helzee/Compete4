#include "gameListMenu.h"
#include "../constants.h"
#include "../gameSessionDB.h"
#include "menu.h"

using namespace std;

GameListMenu::GameListMenu()
{
   header = "List of available games:\n------------------------";
   type = GAMELIST;
}

/*
string GameListMenu::refresh(Session* session,
                             const GameSessionDB* gamesDB) const
{
   string buffer = header + "\n";
   buffer += gamesDB->gamesList();
   for (int i = 0; i < buffer.length(); i += MAX_MSG_SIZE)
      session->send(buffer.substr(i, MAX_MSG_SIZE));
}
*/

int GameListMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
}
