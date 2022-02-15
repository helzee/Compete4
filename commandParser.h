#include "constants.h"
#include "session.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

void send(string, int);

bool mainMenuCommand(string command, Session*);
bool loginMenuCommand(string, Session*);

bool parseCommand(string command, Session*);
bool mainMenuCommand(string command, Session* session);
bool loginMenuCommand(string, Session*);

#endif