#include "mainMenu.h"
#include "../globalFuncs.h"
#include "menu.h"
#include "../session.h"

using namespace std;

MainMenu::MainMenu()
{
   header = "------MAIN MENU------\n"
            "login (l): to login or switch current acount";
   type = MAIN;
}

int MainMenu::sendWelcome(Session* session) const
{
   return send(header, session->getSessionID());
}

int MainMenu::loginCommand(CommandTok* comm, Session* session) const {
   return changeMenu(session, LOGIN);
   
}