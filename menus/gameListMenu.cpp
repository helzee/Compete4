#include "gameListMenu.h"
#include "../constants.h"
#include "../gameSessionDB.h"
#include "../session.h"
#include "menu.h"

using namespace std;

GameListMenu::GameListMenu()
{
   header = "\n------Games List Menu------\n";
   type = GAMELIST;
}

int GameListMenu::joinCommand(CommandTok* comm, Session* session) const
{
   return session->joinGame(comm);
}

int GameListMenu::quickCommand(CommandTok* comm, Session* session) const
{
   return session->quickJoin();
}

int GameListMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
}

int GameListMenu::helpCommand(CommandTok* comm, Session* session) const
{
   return session->send(LIST_HELP_TEXT);
}

int GameListMenu::listCommand(CommandTok* comm, Session* session) const
{
   if (session->getRecord() == nullptr) {
      session->send("You must sign in before joining a game.");
      return 1;
   }

   if (changeMenu(session, GAMELIST)) {
      session->listGames();
      return 0;
   }
   session->listGames();
   return 1;
}

int GameListMenu::createCommand(CommandTok* comm, Session* session) const
{
   if (session->getRecord() == nullptr) {
      session->send("You must sign in before joining a game.");
      return 1;
   }

   return session->createGame();
}