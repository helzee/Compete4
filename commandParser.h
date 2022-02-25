#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "constants.h"

class CommandTok;
class Session;

using namespace std;
int parseCommand(string, Session*);

#endif
