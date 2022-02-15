#include "constants.h"

int sessionCounter = 0;
int getNewSessionID() { return sessionCounter++; }

class Session
{
private:
   int sessionID;

public:
   char* name = "John Doe";
   int currMenu = 0;
   int currGameID = 0;

   Session() { sessionID = getNewSessionID(); }

   bool operator==(const Session& rhs) const
   {
      return sessionID == rhs.sessionID;
   }
   bool operator<(const Session& rhs) const
   {
      return sessionID < rhs.sessionID;
   }
   bool operator>(const Session& rhs) const
   {
      return sessionID > rhs.sessionID;
   }
};