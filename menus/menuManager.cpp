#include "menuManager.h"

#include "mainMenu.h"
#include "loginMenu.h"
#include "guestMenu.h"
#include "signInMenu.h"
#include "makeAccMenu.h"
#include "restrictedMenu.h"
#include "menu.h"



MenuManager::MenuManager() {
   
}
void MenuManager::addMenu(const Menu* menu, MenuType index){
   allMenus[index] = menu;
}

const Menu* MenuManager::getMenu(MenuType menu) const { 
   return allMenus[menu]; }

void MenuManager::buildMenus() { 
   allMenus[MAIN] = new MainMenu();
   allMenus[MENU] = new Menu();
   allMenus[GUEST] = new GuestMenu();
   allMenus[LOGIN] = new LoginMenu();
   allMenus[MAKEACCOUNT] = new MakeAcctMenu();
   allMenus[SIGNIN] = new SignInMenu();
}