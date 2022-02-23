

#ifndef SIGNINMENU_H
#define SIGNINMENU_H
#include "../constants.h"

#include "restrictedMenu.h"
class Session;
class CommandTok;


using namespace std;

class SignInMenu : public RestrictedMenu {
   public:
      SignInMenu();

   private:
      virtual int badCommand(CommandTok* comm, Session* session) const;
      virtual int backCommand(CommandTok* comm, Session* session) const;
      
};



#endif