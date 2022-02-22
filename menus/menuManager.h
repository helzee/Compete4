#ifndef MENUBUILDER_H
#define MENUBUILDER_H
#include "../constants.h"
#include "menu.h"

using namespace std;



class MenuManager {
   public:
   
   MenuManager();

   
   const Menu* getMenu(MenuType menu) const;
   void addMenu(const Menu*, MenuType menu);
   void buildMenus();

private:
   const Menu* allMenus[NUM_OF_MENUS];
};



#endif