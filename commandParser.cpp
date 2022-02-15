#include "commandParser.h"

// Return false if the command was quit/exit
bool parseCommand(string command, Session* session)
{
   // global commands
   if (cmp(command, "quit") || cmp(command, "exit")) {
      return false;
   }
   if (cmp(command, "leaderboard")) {
      send("You are viewing the leaderboard", session->clientSd);
      return true;
   }

   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(command, session);
      break;
   case LOGIN:
      return loginMenuCommand(command, session);
      break;
   default:
      send("ERROR: You are went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
   }

   return true;
}