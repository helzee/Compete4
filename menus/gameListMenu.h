#ifndef GAMELISTMENU_H
#define GAMELISTMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class GameListMenu : public Menu
{
public:
   GameListMenu();

protected:
   virtual int joinCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int listCommand(CommandTok* comm, Session* session) const;

   const char* LIST_HELP_TEXT =
       "\n---List of Games List commands---\n"
       "Format is \"name (valid other ways to type it): explanation\"\n\n"

       "list (ls): re-print/refresh list of games\n"
       "join <#> (j <#>): tries to join the game with the index <#>\n"
       "main: go to the main menu\n\n"

       "help (h): self explanatory\n"
       "exit (quit, q) : quit the game\n"
       "leaderboard (lb) : view leaderboard"
       "print (p) : re-print the current menu\n"
       "name (n) : print your username\n"
       "back (b) : go back to previous menu";
};

#endif