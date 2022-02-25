

#ifndef RESTRICTEDMENU_H
#define RESTRICTEDMENU_H
#include "../constants.h"
#include "menu.h"

class Session;
class CommandTok;
class RestrictedMenu;

using namespace std;

// a menu with a very specific task. cant do much else here
class RestrictedMenu : public Menu
{
public:
   RestrictedMenu();

protected:
   virtual int badCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int exitCommand(CommandTok* comm, Session* session) const;
   virtual int printCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int nameCommand(CommandTok* comm, Session* session) const;
   virtual int loginCommand(CommandTok* comm, Session* session) const;
   virtual int signinCommand(CommandTok* comm, Session* session) const;
   virtual int makeAcctCommand(CommandTok* comm, Session* session) const;
   virtual int lBoardCommand(CommandTok* comm, Session* session) const;
   virtual int mainCommand(CommandTok* comm, Session* session) const;
   virtual int guestCommand(CommandTok* comm, Session* session) const;
};

#endif