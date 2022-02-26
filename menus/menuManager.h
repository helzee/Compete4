#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include "../constants.h"
#include "menu.h"

using namespace std;

// menu types  enum declared in constants.h

class MenuManager
{
public:
   MenuManager();

   const Menu* getMenu(MenuType menu) const;
   void addMenu(const Menu*, MenuType menu);
   void buildMenus();

private:
   const Menu* allMenus[NUM_OF_MENUS];
};

#endif