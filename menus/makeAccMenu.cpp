#include "makeAccMenu.h"
#include "menu.h"
#include "menuManager.h"

using namespace std;

MakeAcctMenu::MakeAcctMenu() { 
   type = MAKEACCOUNT; 
   menuManager.addMenu(this, MAKEACCOUNT);
   }