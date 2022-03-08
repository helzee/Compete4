#ifndef LOGINMENU_H
#define LOGINMENU_H
#include "../constants.h"
#include "menu.h"

class Session;
class CommandTok;
class RestrictedMenu;

using namespace std;

class LoginMenu : public Menu
{
public:
   LoginMenu();

protected:
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int signinCommand(CommandTok* comm, Session* session) const;
   virtual int makeAcctCommand(CommandTok* comm, Session* session) const;
   virtual int guestCommand(CommandTok* comm, Session* session) const;
   virtual int logoutCommand(CommandTok* comm, Session* session) const;

   const char* LOGIN_HELP_TEXT =
       "\n---List of Login menu commands---\n"
       "Format is \"name (valid other ways to type it): explanation\"\n\n"

       "sigin (s): sign in to an existing account\n"
       "makeaccount (m): make a new account\n"
       "guest (g): make a temporary guest account\n"
       "logout (lo): log out of your current account\n"
       "main: go to the main menu\n\n"

       "help (h): self explanatory\n"
       "exit (quit, q) : quit the game\n"
       "leaderboard (lb) : view leaderboard"
       "print (p) : re-print the current menu\n"
       "name (n) : print your username\n"
       "back (b) : go back to previous menu";
};

#endif