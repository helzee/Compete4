#include "constants.h"
#include "globalFuncs.h"
#include "session.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

bool parseCommand(string command, Session*);
void mainMenuCommand(string, Session*);
void loginMenuCommand(string, Session*);

#endif