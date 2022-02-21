
#include "commandLexer.h"


#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

class Session;
using namespace std;

enum MENU { MAIN, LOGIN, SIGNIN, MAKEACCOUNT, GUEST };

bool parseCommand(string, Session*);
void mainMenuCommand(CommandTok*, Session*);

#endif

