#include "loginCommands.h"
#include "commandParser.h"
#include "globalFuncs.h"
#include "commandLexer.h"
#include "session.h"
#include "userRecordDB.h"


// I'm slowly turning these command functions into menus -Josh
// planning to delete this file when finished


bool makeAccountCommand(Session* session)
{
   string username, password;

   // Get username
   while (true) {
      send("Please enter your desired username: ", session->clientSd);
      username = recieve(session->clientSd);

      if (cmp(username, "exit") || cmp(username, "quit"))
         return false;
      if (checkReturn(username, session))
         return true;

      if (username.length() < 4 || (username[0] == 'G' && username[1] == ':')) {
         send("Username invalid (must be 4 chars or longer, not starting with "
              "\'G:\'):",
              session->clientSd);
         continue;
      }
      if (checkIfRecord(username)) {
         send("Username taken, try again:", session->clientSd);
         continue;
      }

      break;
   }

   send("Username is valid and available.", session->clientSd);

   // Get password
   while (true) {
      send("Please enter desired password:", session->clientSd);
      password = recieve(session->clientSd);

      if (cmp(password, "exit") || cmp(password, "quit"))
         return false;
      if (checkReturn(password, session))
         return true;

      if (password.length() < 5) {
         send("Password must be at least 5 chars long.", session->clientSd);
         continue;
      }

      break;
   }

   session->record = makeRecord(username, encrypt(password));
   if (session->record == nullptr) {
      send("Error occured: Could not make account. Please try again.",
           session->clientSd);
      return makeAccountCommand(session);
   }

   send("Signed up successfully, going to main menu.", session->clientSd);
   session->currMenu = MAIN;
   return true;
}

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

