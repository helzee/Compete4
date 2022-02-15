#include "loginCommands.h"
#include "commandParser.h"

bool loginMenuCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      return true;
   }
   if (cmp(command, "print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest, \"l\" to log out.",
           session->clientSd);
      return true;
   }
   if (cmp(command, "s")) {
      return signInCommand(session);
   }
   if (cmp(command, "m")) {
      return makeAccountCommand(session);
   }
   if (cmp(command, "g")) {
      return signInAsGuestCommand(session);
   }
   if (cmp(command, "l")) {
      if (session->record != nullptr) {
         send("Signed out successfully.", session->clientSd);
         session->record = nullptr;
      } else
         send("You are not signed in.", session->clientSd);

      send("Going to main menu.", session->clientSd);
      session->currMenu = MAIN;
      return true;
   }

   send("Not a recognized command, try again.", session->clientSd);
   return true;
}

bool signInCommand(Session* session)
{
   string input;
   Record* playerRecord;

   send("Please enter username to sign in:", session->clientSd);
   input = recieve(session->clientSd);

   while (true) {
      if (cmp(input, "exit") || cmp(input, "quit"))
         return false;
      if (checkReturn(input, session))
         return true;

      playerRecord = getRecord(input);
      if (playerRecord == nullptr) {
         send("Username not found, try again:", session->clientSd);
         input = recieve(session->clientSd);
         continue;
      }

      session->record = playerRecord;
      send("Signed in successfully.", session->clientSd);
      send("Going to main menu.", session->clientSd);
      session->currMenu = MAIN;
      return true;
   }
}

bool makeAccountCommand(Session* session)
{
   string input;
   Record* checkRecord;

   send("Please enter your desired username: ", session->clientSd);
   input = recieve(session->clientSd);

   while (true) {
      if (cmp(input, "exit") || cmp(input, "quit"))
         return false;
      if (checkReturn(input, session))
         return true;

      if (input.length() < 4 || (input[0] == 'G' && input[1] == ':')) {
         send("Username invalid (must be 4 chars or longer, not starting with "
              "\'G:\'):",
              session->clientSd);
         input = recieve(session->clientSd);
         continue;
      }

      checkRecord = getRecord(input);
      if (checkRecord != nullptr) {
         send("Username taken, try again:", session->clientSd);
         input = recieve(session->clientSd);
         continue;
      }

      session->record = makeRecord(input);
      send("Signed up successfully.", session->clientSd);
      send("Going to main menu.", session->clientSd);
      session->currMenu = MAIN;
      return true;
   }
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

   session->record = new Record("G: " + input);
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
      loginMenuCommand("print", session);
      return true;
   }
   return false;
}