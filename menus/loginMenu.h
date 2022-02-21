

#ifndef LOGINMENU_H
#define LOGINMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class LoginMenu : Menu {
   public:
      LoginMenu();

   private:
      MenuType type;
};

#endif