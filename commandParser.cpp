#include "constants.h"
#include "session.cpp"

bool mainMenuCommand(char* command, Session* session);
bool loginMenuCommand(char* command, Session* session);

bool parseCommand(char* command, Session* session)
{
   switch (session->currMenu) {
   case 0:
      return mainMenuCommand(command, session);
   case 1:
      return loginMenuCommand(command, session);
   default:
      return false;
   }
}

bool mainMenuCommand(char* command, Session* session)
{
   return (strlen(command) > 0);
}

bool loginMenuCommand(char* command, Session* session)
{
   return (strlen(command) > 0);
}