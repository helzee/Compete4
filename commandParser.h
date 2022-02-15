#include "constants.h"
#include "globalFuncs.h"
#include "session.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

bool parseCommand(string command, Session*);
bool mainMenuCommand(string command, Session* session);
bool loginMenuCommand(string, Session*);

#endif