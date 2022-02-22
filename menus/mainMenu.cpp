#include "mainMenu.h"
#include "../globalFuncs.h"
#include "menu.h"
#include "../session.h"
#include "menuManager.h"

using namespace std;

MainMenu::MainMenu()
{
   header = "------MAIN MENU------\n"
            "login (l): to login or switch current acount";
   type = MAIN;
   //menuManager.addMenu(this, MAIN);
}

int MainMenu::sendWelcome(Session* session) const
{
   return session->send(header);
}

int MainMenu::loginCommand(CommandTok* comm, Session* session) const {
   return changeMenu(session, LOGIN);
   
}