
#include "session.h"
#include "userRecord.h"
#include "userRecordDB.h"

#ifndef LOGINCOMMANDS_H
#define LOGINCOMMANDS_H

using namespace std;

bool loginMenuCommand(CommandTok, Session*);
bool signInCommand(Session*);
bool makeAccountCommand(Session*);
bool signInAsGuestCommand(Session*);
bool checkReturn(string, Session*);
int encrypt(string);
unsigned int turnToInt(string);

#endif