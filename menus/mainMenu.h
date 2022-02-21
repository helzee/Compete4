

#ifndef MAINMENU_H
#define MAINMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class MainMenu : public Menu
{
public:
   MainMenu();

private:
   MenuType type;
   int sendWelcome(Session* session) const;
   virtual int loginCommand(CommandTok* comm, Session* session) const;
};

static const MainMenu* mainMenu = new MainMenu();

#endif