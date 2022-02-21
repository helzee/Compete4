

#ifndef GUESTMENU_H
#define GUESTMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class GuestMenu : Menu {
   public:
      GuestMenu();

   private:
      MenuType type;
};

#endif