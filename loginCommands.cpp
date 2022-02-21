#include "loginCommands.h"
#include "commandParser.h"
#include "openssl/sha.h"
#include "globalFuncs.h"
#include "commandLexer.h"

bool loginMenuCommand(CommandTok* command, Session* session)
{

   switch (command->getType()) {
   case (TOKMAIN):
   case (TOKBACK):
      send("Going to main menu.", session->clientSd);
      session->currMenu = MAIN;
      return true;
   case (TOKPRINT):
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest, \"l\" to log out.",
           session->clientSd);
      return true;
   case (TOKSIGNIN):
      return signInCommand(session);
   case (TOKMAKEACCT):
      return makeAccountCommand(session);
   case (TOKGUEST):
      return signInAsGuestCommand(session);
   // reusing login token for logout!s
   case (TOKLOGIN):
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
   string username, password;
   Record* playerRecord;

   // Get username
   while (true) {
      send("Please enter username to sign in:", session->clientSd);
      username = recieve(session->clientSd);

      if (cmp(username, "exit") || cmp(username, "quit"))
         return false;
      if (checkReturn(username, session))
         return true;

      if (checkIfRecord(username))
         break;
      send("Username not found, try again:", session->clientSd);
   }

   send("Username found.", session->clientSd);

   // Get password
   while (true) {
      send("Please enter password:", session->clientSd);
      password = recieve(session->clientSd);

      if (cmp(password, "exit") || cmp(password, "quit"))
         return false;
      if (checkReturn(password, session))
         return true;

      playerRecord = getRecord(username, encrypt(password));
      if (playerRecord == nullptr)
         send("Password incorrect.", session->clientSd);
      else
         break;
   }

   session->record = playerRecord;
   send("Signed in successfully. Going to main menu.", session->clientSd);
   session->currMenu = MAIN;
   return true;
}

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

// Uses basic Rabin Function
int encrypt(string password)
{
   // Cast the password into an unsigned int
   // Then turn it into a long unsigned int, therefore making upper-half empty
   auto number = (long unsigned int)turnToInt(password);

   // Square the number
   number = number * number;
   return (int)(number % HASH_NUMBER);
}

unsigned int turnToInt(string password)
{
   unsigned int toReturn = 0;
   unsigned int toXOR;
   unsigned short int letter;

   for (int i = 0; i < password.length(); i++) {
      letter = (unsigned short int)password[i];

      // toXOR = (letter^2 + letter)^2 + letter
      // toXOR will be at most 32 bits long: an unsigned int
      toXOR = letter + letter * letter;
      toXOR = toXOR * toXOR + letter;

      // toReturn = (toReturn * 2) XOR toXOR
      toReturn *= 2;
      toReturn = toReturn ^ toXOR;
   }

   return toReturn;
}