#ifndef GAMELISTMENU_H
#define GAMELISTMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class GameListMenu : public Menu
{
public:
   GameListMenu();

private:
   virtual int backCommand(CommandTok* comm, Session* session) const;
};

#endif