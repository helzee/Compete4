/** @file session.h
 *
 */
#include "constants.h"

#ifndef SESSION_H
#define SESSION_H


using namespace std;

class Session
{
public:
   char username[MAX_NAME];
   int currMenu;
   int currGameID;
   int clientSd;

   Session(int sd, int id);
   int getSessionID();

private:
   int sessionID;
   
   
};

#endif