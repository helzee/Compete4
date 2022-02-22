

#ifndef MENU_H
#define MENU_H
#include "../constants.h"



using namespace std;

class CommandTok;
class Session;

#define NUM_MENUS 6

/**
 * @brief Menu class (parent of all menus)
 *
 */
class Menu
{
public:
  
  
   int navigate(CommandTok* comm, Session* session) const;
   Menu();
   MenuType getType() const;

protected:
   
   int changeMenu(Session* session, MenuType menu) const;
   virtual int sendWelcome(Session* session) const;
   int sendBadCommand(Session* session) const;
   const Menu** allMenus;

   virtual int badCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int exitCommand(CommandTok* comm, Session* session) const;
   virtual int printCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int nameCommand(CommandTok* comm, Session* session) const;
   virtual int loginCommand(CommandTok* comm, Session* session) const;
   virtual int signinCommand(CommandTok* comm, Session* session) const;
   virtual int makeAcctCommand(CommandTok* comm, Session* session) const;
   virtual int lBoardCommand(CommandTok* comm, Session* session) const;
   virtual int mainCommand(CommandTok* comm, Session* session) const;
   virtual int guestCommand(CommandTok* comm, Session* session) const;

   int sendGlobalHelp(Session* session) const;

   const char* HELP_TEXT1 = "List of global commands:\n"
                            "help (h): self explanatory\n"
                            "exit (quit, q) : quit the game\n"
                            "leaderboard (lb) : view leaderboard";
   const char* HELP_TEXT2 = "print (p) : re-print the current menu\n"
                            "name (n) : print your username\n"
                            "back (b) : go back to previous menu";

   const char* LBOARD_TEXT = "You are viewing the leaderboard";
   const char* BADCOMMAND_TEXT = "Not a recognized command, try again.";

    MenuType type;
    const char* header;
   
   private:
    
};




#endif
