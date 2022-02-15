#include "constants.h"
#include "globalFuncs.h"
#include "loginCommands.h"
#include "session.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

bool parseCommand(string, Session*);
void mainMenuCommand(string, Session*);

#endif