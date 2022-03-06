#include "loginMenu.h"
#include "../session.h"
#include "menu.h"
#include "menuManager.h"

using namespace std;

LoginMenu::LoginMenu()
{
   // swap l and s. l to login. s to signout
   header = "\n------Login Menu------\n"
            "Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
            "sign in as guest, \"lo\" to log out.";
   this->type = LOGIN;
}

int LoginMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
}

int LoginMenu::helpCommand(CommandTok* comm, Session* session) const
{
   return session->send(LOGIN_HELP_TEXT);
}

int LoginMenu::signinCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, SIGNIN);
}
int LoginMenu::makeAcctCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAKEACCOUNT);
}
int LoginMenu::guestCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, GUEST);
}

int LoginMenu::logoutCommand(CommandTok* comm, Session* session) const
{
   if (session->signOut())
      session->send("Signed out successfully.");
   else
      session->send("You are not signed in.");

   return changeMenu(session, MAIN);
}