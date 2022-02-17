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
   default:
      send("ERROR: You are went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
   }

   return true;
}

void mainMenuCommand(string command, Session* session)
{
   if (cmp(command, "help")) {
      send(MAIN_HELP, session->clientSd);
   }

   else if (cmp(command, "login")) {
      session->currMenu = LOGIN;
      loginMenuCommand("print", session);
   }

   else if (cmp(command, "print")) {
      send("You are in the Main Menu", session->clientSd);
   }

   else if (cmp(command, "name")) {
      if (session->record != nullptr) {
         string name = "Your name is " + session->record->getName();
         send(name, session->clientSd);
      } else
         send("You are not logged in.", session->clientSd);
   }

   else
      send("Not a recognized command, try again.", session->clientSd);
}