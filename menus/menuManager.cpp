#include "menuManager.h"
#include "../constants.h"
#include "gameListMenu.h"
#include "guestMenu.h"
#include "ingameMenu.h"
#include "loginMenu.h"
#include "mainMenu.h"
#include "makeAccMenu.h"
#include "makePasswordMenu.h"
#include "menu.h"
#include "passwordMenu.h"
#include "restrictedMenu.h"
#include "signInMenu.h"

MenuManager::MenuManager() { buildMenus(); }
void MenuManager::addMenu(const Menu* menu, MenuType index)
{
   allMenus[index] = menu;
}

const Menu* MenuManager::getMenu(MenuType menu) const { return allMenus[menu]; }

void MenuManager::buildMenus()
{
   allMenus[MAIN] = new MainMenu();
   allMenus[MENU] = new Menu();
   allMenus[GUEST] = new GuestMenu();
   allMenus[LOGIN] = new LoginMenu();
   allMenus[MAKEACCOUNT] = new MakeAcctMenu();
   allMenus[SIGNIN] = new SignInMenu();
   allMenus[PASSWORD] = new PasswordMenu();
   allMenus[MAKEPASSWORD] = new MakePasswordMenu();
   allMenus[GAMELIST] = new GameListMenu();
   allMenus[INGAME] = new InGameMenu();
}