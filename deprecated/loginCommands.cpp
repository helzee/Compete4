#include "loginCommands.h"
#include "commandParser.h"
#include "globalFuncs.h"
#include "commandLexer.h"
#include "session.h"
#include "userRecordDB.h"


// I'm slowly turning these command functions into menus -Josh
// planning to delete this file when finished




bool signInAsGuestCommand(Session* session)
{
   string input;

   send("Please enter desired guest name: ", session->clientSd);
   input = recieve(session->clientSd);

   if (cmp(input, "exit") || cmp(input, "quit"))
      return false;
   if (checkReturn(input, session))
      return true;

   session->record = new Record("G: " + input, 0);
   send("Signed in as guest successfully.", session->clientSd);
   send("Going to main menu.", session->clientSd);
   session->currMenu = MAIN;
   return true;
}

bool checkReturn(string input, Session* session)
{
   if (cmp(input, "main")) {
      session->currMenu = MAIN;
      return true;
   }
   if (cmp(input, "back")) {
      parseCommand("print", session);
      return true;
   }
   return false;
}

