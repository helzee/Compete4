#ifndef PASSWORDMENU_H
#define PASSWORDMENU_H
#include "../constants.h"
#include "signInMenu.h"

using namespace std;

#define MIN_PASSWORD 6
#define MAX_PASSWORD 32

class PasswordMenu : public SignInMenu {
   public:
      PasswordMenu();

   protected:
      virtual int badCommand(CommandTok* comm, Session* session) const;
};

#endif