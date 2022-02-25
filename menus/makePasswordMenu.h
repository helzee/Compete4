#ifndef MAKEPASSWORDMENU_H
#define MAKEPASSWORDMENU_H
#include "../constants.h"
#include "makeAccMenu.h"

using namespace std;

class MakePasswordMenu : public MakeAcctMenu
{
public:
   MakePasswordMenu();

protected:
   virtual int badCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;

private:
   int checkPassword(CommandTok* comm, Session* session) const;
};

#endif