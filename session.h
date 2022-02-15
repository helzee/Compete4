/** @file session.h
 *
 */
#include "constants.h"
#include "userRecord.h"

#ifndef SESSION_H
#define SESSION_H

class gameSession
{
};

using namespace std;

class Session
{
public:
   int currMenu = 0;
   int clientSd;
   Record* record = nullptr;
   gameSession* currGame = nullptr;

   Session(int, int);
   int getSessionID();

private:
   int sessionID;
};

#endif