#include "commandParser.h"

// Return false if the command was quit/exit
bool parseCommand(string command, Session* session)
{
   // first step: check for global commands
   CommandTok commTok = CommandLexer::lexCommand(command.c_str());
   switch (commTok) {
   case TOKHELP:
      send(HELP_TEXT, session->clientSd);
      return true;
   case TOKEXIT:
      return false;
   case TOKLBOARD:
      send(LBOARD_TEXT, session->clientSd);
      return true;
   case TOKNAME:
      if (session->record != nullptr) {
         string name = "Your name is " + session->record->getName() + "\n";
         send(name, session->clientSd);
      } else
         send("You are not logged in.\n", session->clientSd);
      return true;
   }

   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(commTok, session);
      break;
   case LOGIN:
      return loginMenuCommand(command, session);
   default:
      send("ERROR: You went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand(TOKPRINT, session);
   }

   return true;
}

void mainMenuCommand(CommandTok command, Session* session)
{

   switch (command) {
   case TOKLOGIN:
      session->currMenu = LOGIN;
      loginMenuCommand("print", session);
      return;
   case TOKPRINT:
      send(MAIN_MENU_HEADER, session->clientSd);
      return;
   case TOKBAD:
      send("Not a recognized command, try again.", session->clientSd);
      return;
   }

   return;


}