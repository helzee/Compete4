#include "commandParser.h"

bool parseCommand(string command, Session* session)
{
   // global commands
   if (cmp(command, "quit") || cmp(command, "exit")) {
      return false;
   }
   if (cmp(command, "leaderboard")) {
      send("You are viewing the leaderboard\n", session->clientSd);
      return true;
   }

   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(command, session);
   case LOGIN:
      loginMenuCommand(command, session);
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
   if (cmp(command, "login")) {
      session->currMenu = LOGIN;
      loginMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("You are in the Main Menu\n", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.\n", session->clientSd);
}

bool loginMenuCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest\n",
           session->clientSd);
      return;
   }
   if (cmp(command, "s")) {
      // Sign in page
      return;
   }
   if (cmp(command, "m")) {
      // Make account page
      return;
   }
   if (cmp(command, "g")) {
      // Guest login page
      return;
   }

   send("Not a recognized command, try again.\n", session->clientSd);
}