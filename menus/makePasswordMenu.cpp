#include "makePasswordMenu.h"
#include "../session.h"
#include "makeAccMenu.h"
#include "../commandLexer.h"
#include "../constants.h"

using namespace std;

MakePasswordMenu::MakePasswordMenu() {
   header = "Please enter desired password:";
  
   this->type = MAKEPASSWORD;
}

int MakePasswordMenu::checkPassword(CommandTok* comm, Session* session) const {
   string password = comm->getLex();
   if (!session->isPasswordValid(password)) {
      return 1;
   }
   session->send("Password valid.");
   if (!session->makeRecord(password)) {
      return changeMenu(session, MAKEACCOUNT);
      
   }
   session->send("Signed up successfully, going to main menu.");
   return changeMenu(session, MAIN);
}

int MakePasswordMenu::badCommand(CommandTok* comm, Session* session) const {
   return checkPassword(comm, session);
}
int MakePasswordMenu::backCommand(CommandTok* comm, Session* session) const {
   return changeMenu(session, MAKEACCOUNT);
}
