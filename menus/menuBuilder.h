#ifndef MENUBUILDER_H
#define MENUBUILDER_H
#include "constants.h"
class Menu;

enum MenuType { MENU = 0, MAIN, LOGIN, SIGNIN, MAKEACCOUNT, GUEST };

Menu** allMenus;

Menu** buildMenus();

#endif