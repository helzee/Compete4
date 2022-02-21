#include "signInMenu.h"
#include "menu.h"
#include "restrictedMenu.h"
#include "../commandLexer.h"
#include "../globalFuncs.h"
#include "../userRecordDB.h"
#include "../session.h"
#include "../userRecord.h"

using namespace std;

SignInMenu::SignInMenu() {
   header = "Please enter username to sign in:";
   type = SIGNIN;
}



int SignInMenu::badCommand(CommandTok* comm, Session* session) const {
   //first, check validity
   const char* lexeme = comm->getLex();
   int size = 0;
   // while no whitespace and not at end
   while (*lexeme != '\0' && *lexeme != ' ' && *lexeme != '\t') {
      size++;
      lexeme++;
   }
   if (size < MIN_UNAME || size > MAX_UNAME) {
      return send("Username must be between 4 and 32 characters (inclusive)",
                  session->getSessionID());
   }
   string username(comm->getLex());
   username = username.substr(0, size);
   // if username doesn't exist
   if (!checkIfRecord(username)) {
      return send("Username not registered.", session->getSessionID());
   }

   send("Username found.", session->getSessionID());

   //go to password page? or implement login command loop

   // get password

   return 0;
}

int SignInMenu::backCommand(CommandTok* comm, Session* session) const {
   return changeMenu(session, LOGIN);
}