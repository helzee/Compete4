#ifndef PASSWORDMENU_H
#define PASSWORDMENU_H
#include "../constants.h"
#include "signInMenu.h"

using namespace std;



class PasswordMenu : public SignInMenu
{
public:
   PasswordMenu();

protected:
   virtual int badCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;

private:
   int checkPassword(CommandTok* comm, Session* session) const;
};

#endif