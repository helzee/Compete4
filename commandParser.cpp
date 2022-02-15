#include "commandParser.h"

bool parseCommand(string command, Session* session)
{
   if (command.compare("quit") == 0 || command.compare("exit") == 0) {
      return false;
   }
   if (command.copmare("leaderboard") == 0) {
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
   if (command.compare("login") == 0) {
      session->currMenu = LOGIN;
      loginMenuCommand("print", session);
      return;
   }
   if (command.compare("print") == 0) {
      send("You are in the Main Menu\n", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.\n", session->clientSd);
}

bool loginMenuCommand(string command, Session* session)
{
   if (command.compare("main") == 0 || command.compare("back") == 0) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (command.compare("print") == 0) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest\n",
           session->clientSd);
      return;
   }
   if (command.compare("s") == 0) {
      // Sign in page
      return;
   }
   if (command.compare("m") == 0) {
      // Make account page
      return;
   }
   if (command.compare("g") == 0) {
      // Guest login page
      return;
   }

   send("Not a recognized command, try again.\n", session->clientSd);
}