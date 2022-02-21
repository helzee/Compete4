

#ifndef SIGNINMENU_H
#define SIGNINMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class SignInMenu : Menu {
   public:
      SignInMenu();

   private:
      MenuType type;
};

#endif