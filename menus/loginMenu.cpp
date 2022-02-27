#include "loginMenu.h"
#include "../session.h"
#include "menu.h"
#include "menuManager.h"

using namespace std;

LoginMenu::LoginMenu()
{
   // swap l and s. l to login. s to signout
   header = "Please enter \"s\" to sign in, \"m\" to make account, \"g\" to "
            "sign in as guest, \"l\" to log out.";
   this->type = LOGIN;
}

int LoginMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, MAIN);
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

// make logout command. change regex to allow for that without login confusion
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// rough of new algo
// if (session->record != nullptr) {
//    send("Signed out successfully.", session->clientSd);
//    session->record = nullptr;
// } else
//    send("You are not signed in.", session->clientSd);

// send("Going to main menu.", session->clientSd);
// session->currMenu = MAIN;
// return true;
