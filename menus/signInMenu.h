

#ifndef SIGNINMENU_H
#define SIGNINMENU_H
#include "../constants.h"

#include "restrictedMenu.h"

#define MIN_UNAME 4
#define MAX_UNAME 32

using namespace std;

class SignInMenu : public RestrictedMenu {
   public:
      SignInMenu();

   private:
      virtual int badCommand(CommandTok* comm, Session* session) const;
      virtual int backCommand(CommandTok* comm, Session* session) const;
};

static const SignInMenu* signInMenu = new SignInMenu();

#endif