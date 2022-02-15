#include "commandParser.h"

bool loginMenuCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return true;
   }
   if (cmp(command, "print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest",
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

   send("Not a recognized command, try again.", session->clientSd);
   return true;
}

bool signInCommand(Session* session)
{
   string input;
   Record* playerRecord;

   while (true) {
      send("Please enter username to sign in: ", session->clientSd);
      input = recieve(session->clientSd);

      if (cmp(input, "exit") || cmp(input, "quit"))
         return false;
      if (checkReturn(input, session))
         return true;

      playerRecord = getRecord(input);
      if (playerRecord == nullptr) {
         send("Username not found, try again.", session->clientSd);
         continue;
      }

      session->record = playerRecord;
      send("Signed in successfully.", session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return true;
   }
}

bool makeAccountCommand(Session* session)
{
   string input;
   Record* checkRecord;

   while (true) {
      send("Please enter your desired username: ", session->clientSd);
      input = recieve(session->clientSd);

      if (cmp(input, "exit") || cmp(input, "quit"))
         return false;
      if (checkReturn(input, session))
         return true;

      checkRecord = getRecord(input);
      if (checkRecord != nullptr) {
         send("Username taken, try again.", session->clientSd);
         continue;
      }

      session->record = makeRecord(input);
      send("Signed up successfully.", session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return true;
   }
}

bool signInAsGuestCommand(Session* session)
{
   string input;

   while (true) {
      send("Please enter desired guest name: ", session->clientSd);
      input = recieve(session->clientSd);

      if (cmp(input, "exit") || cmp(input, "quit"))
         return false;
      if (checkReturn(input, session))
         return true;

      session->record = new Record(input);
      send("Signed in as guest successfully.", session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return true;
   }
}

bool checkReturn(string input, Session* session)
{
   if (cmp(input, "main")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return true;
   }
   if (cmp(input, "back")) {
      send("Returning to login screen.", session->clientSd);
      return true;
   }
   return false;
}