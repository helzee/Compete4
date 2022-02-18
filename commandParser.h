
#include "session.h"
#include "commandLexer.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;



bool parseCommand(string, Session*);
void mainMenuCommand(CommandTok, Session*);

#endif

