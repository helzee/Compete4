
#ifndef SESSIONSDB_H
#define SESSIONSDB_H
#include "constants.h"

class MenuManager;

class Session;
Session* makeSession(int, const MenuManager*);

bool removeSession(int);

Session* getSession(int);

#endif