#ifndef INGAMEMENU_H
#define INGAMEMENU_H
#include "../constants.h"
#include "menu.h"

using namespace std;

class InGameMenu : public Menu
{
public:
   InGameMenu();

protected:
   virtual int dropPieceCommand(CommandTok* comm, Session* session) const;
   virtual int chatCommand(CommandTok* comm, Session* session) const;
   virtual int printCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int exitCommand(CommandTok* comm, Session* session) const;
   virtual int badCommand(CommandTok* comm, Session* session) const;

   const char* GAME_HELP_TEXT =
       "\n---List of In-Game commands---\n"
       "Format is \"name (valid other ways to type it): explanation\"\n\n"

       "send chat (>): sends message following \">\" character to opponent\n"
       "to drop a piece : when it's your turn, simply enter in the desired "
       "drop "
       "column\n\n"

       "help (h): self explanatory\n"
       "exit (quit, q) : quit the game\n"
       "leaderboard (lb) : view leaderboard"
       "stats (st) : view personal statistics"
       "print (p) : re-print the current game-board\n"
       "name (n) : print your username\n"
       "back (b) : go back to previous menu";
};

#endif