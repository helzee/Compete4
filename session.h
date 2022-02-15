/** @file session.h
 *
 */
#ifndef SESSION_H
#define SESSION_H

using namespace std;

class Session
{
public:
   char username[MAX_NAME];
   int currMenu = 0;
   int currGameID = 0;
   int clientSd;

   Session(int, int);
   int getSessionID();

private:
   int sessionID;
};

#endif