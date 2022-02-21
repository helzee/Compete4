#include "commandParser.h"
#include "commandLexer.h"
#include "constants.h"
#include "globalFuncs.h"
#include "loginCommands.h"
#include "session.h"
#include "constants.h"

// helper strings
const char* HELP_TEXT1 = "List of global commands:\n"
                         "help (h): self explanatory\n"
                         "exit (quit, q) : quit the game\n"
                         "leaderboard (lb) : view leaderboard\n";
const char* HELP_TEXT2 = "print (p) : re-print the current menu\n"
                         "name (n) : print your username\n"
                         "back (b) : go back to previous menu\n";

const char* LBOARD_TEXT = "You are viewing the leaderboard\n";
const char* MAIN_MENU_HEADER = "------MAIN MENU------\n"
                               "login (l): to login or switch current acount\n";

// Return false if the command was quit/exit
bool parseCommand(string command, Session* session)
{
   // lexer needs newline to work
   string newLineComm = command + "\n";
   // first step: check for global commands
   CommandTok* commTok = commandLexer.lexCommand(newLineComm.c_str());
   switch (commTok->getType()) {
   case TOKHELP:
      // make max message size bigger to fit this in one? --------------------
      send(HELP_TEXT1, session->clientSd);
      send(HELP_TEXT2, session->clientSd);
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

   // step 2: check for local commands
   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(commTok, session);
      break;
   case LOGIN:
      return loginMenuCommand(commTok, session);
   default:
      send("ERROR: You went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      parseCommand("print", session);
   }

   return true;
}

void mainMenuCommand(CommandTok* command, Session* session)
{

   switch (command->getType()) {
   case TOKLOGIN:
      session->currMenu = LOGIN;
      parseCommand("print", session);
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