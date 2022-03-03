#ifndef GAMELISTMENU_H
#define GAMELISTMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class GameListMenu : public Menu
{
public:
   GameListMenu();

protected:
   virtual int joinCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int listCommand(CommandTok* comm, Session* session) const;
};

#endif