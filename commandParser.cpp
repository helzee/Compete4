#include "commandParser.h"

bool parseCommand(string command, Session* session)
{
   // global commands
   if (cmp(command, "quit") || cmp(command, "exit")) {
      return false;
   }
   if (cmp(command, "leaderboard")) {
      send("You are viewing the leaderboard\n", session->clientSd);
      return true;
   }

   switch (session->currMenu) {
   case MAIN:
      mainMenuCommand(command, session);
   case LOGIN:
      loginMenuCommand(command, session);
   case SIGNIN:
      signInCommand(command, session);
   case MAKEACCOUNT:
      makeAccountCommand(command, session);
   case GUEST:
      signInAsGuestCommand(command, session);
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
      send("You are in the Main Menu\n", session->clientSd);
      return;
   }

   send("Not a recognized command, try again.\n", session->clientSd);
}

bool loginMenuCommand(string command, Session* session)
{
   if (cmp(command, "main") || cmp(command, "back")) {
      session->currMenu = MAIN;
      mainMenuCommand("print", session);
      return;
   }
   if (cmp(command, "print")) {
      send("Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
           "sign in as guest\n",
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

   send("Not a recognized command, try again.\n", session->clientSd);
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

   send("Not a recognized command, try again.\n", session->clientSd);
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

   send("Not a recognized command, try again.\n", session->clientSd);
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

   send("Not a recognized command, try again.\n", session->clientSd);
}
