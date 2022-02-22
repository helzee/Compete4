
#ifndef SESSIONSDB_H
#define SESSIONSDB_H
#include "constants.h"

class Session;
Session* makeSession(int);

bool removeSession(int);

Session* getSession(int);

#endif