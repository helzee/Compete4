#include "guestMenu.h"
#include "../commandLexer.h"
#include "../session.h"
#include "../userRecord.h"
#include "menu.h"

using namespace std;

GuestMenu::GuestMenu()
{
   this->type = GUEST;
   this->header = "Please enter your guest username:";
}

int GuestMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, LOGIN);
}

int GuestMenu::badCommand(CommandTok* comm, Session* session) const
{
   string username = comm->getLex();
   if (!session->isUsernameValid(username))
      return 1;

   session->setPossibleUsername("G: " + username);

   if (!session->signinAsGuest())
      return 1;

   session->send("Your temporary username is now \"G: " + username +
                 "\". All your data will be deleted upon exitting.");
   return changeMenu(session, MAIN);
}