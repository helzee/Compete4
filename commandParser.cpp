#include "commandParser.h"

bool parseCommand(string command, Session* session)
{
   // global commands
   if (cmp(command, "quit") || cmp(command, "exit")) {
      return false;
   }
   if (cmp(command, "leaderboard")) {
      send("You are viewing the leaderboard", session->clientSd);
      return true;
   }

   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(command, session);
      break;
   case LOGIN:
      loginMenuCommand(command, session);
      break;
   case SIGNIN:
      signInCommand(command, session);
      break;
   case MAKEACCOUNT:
      makeAccountCommand(command, session);
      break;
   case GUEST:
      signInAsGuestCommand(command, session);
      break;
   default:
      send("ERROR: You are went to an invalid menu, sending back to main menu",
           session->clientSd);
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
   }

   return true;
}

void mainMenuCommand(string command, Session* session)
{
   if (cmp(command, "login")) {
      session->currMenu = LOGIN;
      loginMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("You are in the Main Menu", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.", session->clientSd);
}

void loginMenuCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest",
           session->clientSd);
      return;
   }
   if (cmp(command, "s")) {
      session->currMenu = SIGNIN;
      signInCommand("print", session);
      return;
   }
   if (cmp(command, "m")) {
      session->currMenu = MAKEACCOUNT;
      makeAccountCommand("print", session);
      return;
   }
   if (cmp(command, "g")) {
      session->currMenu = GUEST;
      signInAsGuestCommand("print", session);
      return;
   }

   send("Not a recognized command, try again.", session->clientSd);
}

void signInCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter username to sign in: ", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.", session->clientSd);
}

void makeAccountCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter your desired username: ", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.", session->clientSd);
}

void signInAsGuestCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter your desired guest name: ", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.", session->clientSd);
}
