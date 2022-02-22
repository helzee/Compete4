



#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "constants.h"
class CommandTok;

class Session;
using namespace std;



bool parseCommand(string, Session*);
void mainMenuCommand(CommandTok*, Session*);

#endif

