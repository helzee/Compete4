#include "constants.h"
#include "globalFuncs.h"
#include "session.h"
#include "userRecord.h"
#include "userRecordDB.h"

#ifndef LOGINCOMMANDS_H
#define LOGINCOMMANDS_H

using namespace std;

bool loginMenuCommand(string, Session*);
bool signIn(Session*);
bool makeAccount(Session*);
bool signInAsGuest(Session*);
bool checkReturn(string, Session*);

#endif