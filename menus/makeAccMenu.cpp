#include "makeAccMenu.h"
#include "../commandLexer.h"
#include "../session.h"
#include "menu.h"
#include "menuManager.h"
#include "restrictedMenu.h"

using namespace std;

MakeAcctMenu::MakeAcctMenu()
{
   type = MAKEACCOUNT;
   header = "Please enter your desired username:";
}

int MakeAcctMenu::backCommand(CommandTok* comm, Session* session) const
{
   return changeMenu(session, LOGIN);
}

int MakeAcctMenu::badCommand(CommandTok* comm, Session* session) const
{
   string username = comm->getLex();
   if (!session->isUsernameValid(username)) {
      return 1;
   }
   if (session->checkIfRecord(comm->getLex())) {
      string sendMsg = "Username \"" + username + "\" already exists.";
      return session->send(sendMsg);
   }
   session->send("Username is valid and available.");
   session->setPossibleUsername(username);

   return changeMenu(session, MAKEPASSWORD);
}
