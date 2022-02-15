#include "commandParser.h"

bool parseCommand(string command, Session* session)
{
   switch (session->currMenu) {
   case MAIN:
      return mainMenuCommand(command, session);
   case LOGIN:
      return loginMenuCommand(command, session);
   default:
      send("ERROR: You are went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      return mainMenuCommand("print", session);
   }
}

bool mainMenuCommand(string command, Session* session)
{
   if (command.compare("quit") == 0 || command.compare("exit") == 0) {
      return false;
   }
   if (command.compare("login") == 0) {
      session->currMenu = LOGIN;
      return loginMenuCommand("print", session);
   }
   if (command.compare("print") == 0) {
      send("You are in the Main Menu\n", session->clientSd);
      return true;
   }

   return false;
}

bool loginMenuCommand(string command, Session* session)
{
   if (command.compare("quit") == 0 || command.compare("exit") == 0) {
      return false;
   }
   if (command.compare("main") == 0 || command.compare("back") == 0) {
      session->currMenu = MAIN;
      return mainMenuCommand("print", session);
   }
   if (command.compare("print") == 0) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest\n",
           session->clientSd);
      return true;
   }
   if (command.compare("s") == 0) {
      // Sign in page
      return true;
   }
   if (command.compare("m") == 0) {
      // Make account page
      return true;
   }
   if (command.compare("g") == 0) {
      // Guest login page
      return true;
   }

   return false;
}