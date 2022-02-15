#include "constants.h"
#include "session.cpp"

void send(string message, int sd)
{
   while (write(sd, message, MAX_MSG_SIZE) != message.length())
      ;
}

bool mainMenuCommand(char* command, Session* session);
bool loginMenuCommand(char* command, Session* session);

bool parseCommand(char* command, Session* session)
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
      mainMenuCommand("print", session);
   }
}

bool mainMenuCommand(char* command, Session* session)
{
   if (strcmp(command, "login") == 0) {
      session->currMenu = LOGIN;
      return loginMenuCommand("print", session);
   }
   if (strcmp(command, "print") == 0) {
      send("You are in the Main Menu", session->clientSd);
      return true;
   }

   return false;
}

bool loginMenuCommand(char* command, Session* session)
{
   if (strcmp(command, "main") == 0 || strcmp(command, "back") == 0) {
      session->currMenu = MAIN;
      return mainMenuCommand("print", session);
   }
   if (strcmp(command, "print") == 0) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest",
           session->clientSd);
      return true;
   }
   if (strcmp(command, "s") == 0) {
      // Sign in page
      return true;
   }
   if (strcmp(command, "m") == 0) {
      // Make account page
      return true;
   }
   if (strcmp(command, "g") == 0) {
      // Guest login page
      return true;
   }

   return false;
}