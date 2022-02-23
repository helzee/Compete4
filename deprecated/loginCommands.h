



#ifndef LOGINCOMMANDS_H
#define LOGINCOMMANDS_H

#include "../constants.h"
class Menu;
class Session;
class CommandTok;
class RestrictedMenu;



using namespace std;

bool loginMenuCommand(CommandTok*, Session*);
bool signInCommand(Session*);
bool makeAccountCommand(Session*);
bool signInAsGuestCommand(Session*);
bool checkReturn(string, Session*);
int encrypt(string);
unsigned int turnToInt(string);

#endif