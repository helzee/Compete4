#include "constants.h"
#include "session.h"
#ifndef SESSIONSDB_H
#define SESSIONSDEB_H

Session* makeSession(int);

bool removeSession(int);



Session* getSession(int);

#endif