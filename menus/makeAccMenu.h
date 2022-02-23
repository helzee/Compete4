

#ifndef MAKEACCMENU_H
#define MAKEACCMENU_H
#include "../constants.h"
#include "menu.h"
#include "restrictedMenu.h"

using namespace std;

class MakeAcctMenu : public RestrictedMenu {
   public:
      MakeAcctMenu();

   protected:
      virtual int backCommand(CommandTok* comm, Session* session) const;
      virtual int badCommand(CommandTok* comm, Session* session) const;


};


#endif