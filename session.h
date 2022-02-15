/** @file session.h
 *
 */
#include "constants.h"
#include "userRecord.h"

#ifndef SESSION_H
#define SESSION_H

using namespace std;

class Session
{
public:
   int currMenu = 0;
   int currGameID = 0;
   int clientSd;
   Record* record = nullptr;

   Session(int, int);
   int getSessionID();

private:
   int sessionID;
};

#endif