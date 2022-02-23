#include "signInMenu.h"
#include "../commandLexer.h"
#include "../globalFuncs.h"
#include "../session.h"
#include "../userRecord.h"
#include "../userRecordDB.h"
#include "../constants.h"
#include "menu.h"
#include "menuManager.h"
#include "restrictedMenu.h"


using namespace std;

SignInMenu::SignInMenu()
{
   header = "Please enter username to sign in:";
   type = SIGNIN;
   // menuManager.addMenu(this, SIGNIN);
}

int SignInMenu::badCommand(CommandTok* comm, Session* session) const
{
   if (!session->isUsernameValid(comm->getLex())) {
      return session->send("Username must be between 4 and 32 characters (inclusive)"
       "and contain no spaces or tabs");
   }
   if (!session->checkIfRecord(comm->getLex())) {
      return session->send("Username not registered.");
   }

   session->send("Username found.");

   return changeMenu(session, PASSWORD);

   return 0;
}

int SignInMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, LOGIN);
}