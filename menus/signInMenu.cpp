#include "signInMenu.h"
#include "../commandLexer.h"
#include "../constants.h"
#include "../globalFuncs.h"
#include "../session.h"
#include "../userRecord.h"
#include "../userRecordDB.h"
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
   // Ensure the username meets basic requirements
   if (!session->isUsernameValid(comm->getLex())) {
      return 1;
   }

   // Then ensure the username exists
   if (!session->checkIfRecord(comm->getLex())) {
      return session->send("Username not registered.");
   }

   // Then ensure the account is not in use
   if (session->isUsernameInUse(comm->getLex())) {
      session->send("Username is in use at the moment. If this is an issue, "
                    "please contact the administators.");
      return 1;
   }

   session->send("Username found and accepted.");

   return changeMenu(session, PASSWORD);

   return 0;
}

int SignInMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, LOGIN);
}