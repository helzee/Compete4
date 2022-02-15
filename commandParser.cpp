#include "commandParser.h"


void send(string message, int sd)
{
   while (write(sd, message.c_str(), MAX_MSG_SIZE) != message.length())
      ;
}

bool mainMenuCommand(string command, Session* session);
bool loginMenuCommand(string command, Session* session);

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
   if (command.compare("login")) {
      session->currMenu = LOGIN;
      return loginMenuCommand("print", session);
   }
   if (command.compare("print")) {
      send("You are in the Main Menu", session->clientSd);
      return true;
   }

   return false;
}

bool loginMenuCommand(string command, Session* session)
{
   if (command.compare("main") || command.compare("back")) {
      session->currMenu = MAIN;
      return mainMenuCommand("print", session);
   }
   if (command.compare("print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest",
           session->clientSd);
      return true;
   }
   if (command.compare("s")) {
      // Sign in page
      return true;
   }
   if (command.compare("m")) {
      // Make account page
      return true;
   }
   if (command.compare("g")) {
      // Guest login page
      return true;
   }

   return false;
}