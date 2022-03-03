#ifndef GUESTMENU_H
#define GUESTMENU_H
#include "../constants.h"
#include "menu.h"
#include "restrictedMenu.h"

using namespace std;

class GuestMenu : public RestrictedMenu
{
public:
   GuestMenu();

protected:
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int badCommand(CommandTok* comm, Session* session) const;
};

#endif