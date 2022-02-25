#include "passwordMenu.h"
#include "../commandLexer.h"
#include "../constants.h"
#include "../session.h"

using namespace std;

PasswordMenu::PasswordMenu()
{
   header = "Please enter password:";
   this->type = PASSWORD;
}

int PasswordMenu::checkPassword(CommandTok* comm, Session* session) const
{
   if (!session->signin(comm->getLex())) {
      return session->send("Password incorrect.");
   }
   session->send("Signed in successfully. Going to main menu.");
   return changeMenu(session, MAIN);
}

int PasswordMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, SIGNIN);
}

int PasswordMenu::badCommand(CommandTok* comm, Session* session) const
{
   return checkPassword(comm, session);
}