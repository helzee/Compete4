

#ifndef MAKEACCMENU_H
#define MAKEACCMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class MakeAcctMenu : public Menu {
   public:
      MakeAcctMenu();

   private:
      MenuType type;
};

const MakeAcctMenu* makeAcctMenu = new MakeAcctMenu();
#endif