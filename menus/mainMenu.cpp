#include "mainMenu.h"
#include "../globalFuncs.h"
#include "../session.h"
#include "menu.h"
#include "menuManager.h"

using namespace std;

MainMenu::MainMenu()
{
   header = "\n------MAIN MENU------\n"
            "Type help or h to see the help menu";
   type = MAIN;
   // menuManager.addMenu(this, MAIN);
}

int MainMenu::sendWelcome(Session* session) const
{
   return session->send(header);
}

int MainMenu::loginCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, LOGIN);
}

int MainMenu::listCommand(CommandTok* comm, Session* session) const
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