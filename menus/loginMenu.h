

#ifndef LOGINMENU_H
#define LOGINMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class LoginMenu : public Menu {
   public:
      LoginMenu();

   private:
      MenuType type;
       virtual int backCommand(CommandTok* comm, Session* session) const;
       virtual int signinCommand(CommandTok* comm, Session* session) const;
       virtual int makeAcctCommand(CommandTok* comm, Session* session) const;
       virtual int guestCommand(CommandTok* comm, Session* session) const;
};

static const LoginMenu loginMenu;

#endif