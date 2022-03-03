

#ifndef INGAMEMENU_H
#define INGAMEMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class InGameMenu : public Menu
{
public:
   InGameMenu();

protected:
   virtual int dropPieceCommand(CommandTok* comm, Session* session) const;
   virtual int printCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int badCommand(CommandTok* comm, Session* session) const;
};

#endif