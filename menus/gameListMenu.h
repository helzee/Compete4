#ifndef GAMELISTMENU_H
#define GAMELISTMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class GameListMenu : public Menu
{
public:
   GameListMenu();
   virtual int joinCommand(CommandTok* comm, Session* session) const;

private:
   virtual int backCommand(CommandTok* comm, Session* session) const;
};

#endif