#include "constants.h"
#include "globalFuncs.h"
#include "session.h"
#include "userRecordDB.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

bool parseCommand(string, Session*);
void mainMenuCommand(string, Session*);
void loginMenuCommand(string, Session*);
void signInCommand(string, Session*);
void makeAccountCommand(string, Session*);
void signInAsGuestCommand(string, Session*);

#endif