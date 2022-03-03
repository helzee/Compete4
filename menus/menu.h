

#ifndef MENU_H
#define MENU_H
#include "../constants.h"

using namespace std;

class CommandTok;
class Session;

#define NUM_MENUS 6

/**
 * @brief Menu class (parent of all menus) All menus inherit
 * from this Menu class. It is not an abstract class (currently), but it
 * should be treated like one. The user should never actually end up in
 * a Menu object. It's primary function is to allow the user to navigate
 * our menu system (with the navigate method)
 *
 * NOTE: HOW TO ADD NEW MENUS
 *
 * 1) in constants.h, define the new menu's enum in MenuType. put it before the
 * final "size" enum
 *
 * 2) create the new menu header. declare it as a class that inherits from
 * another menu (good default is Menu). You can look at other menu's for
 * examples
 *
 * 3) in the header, declare what commands you want to override from the
 * inherited menu
 *
 * 4) implement the new command functions in the new menu's .cpp file. Make sure
 * that in the constructor you specify the menu type and give it a header string
 *
 * 2) in menuManager.cpp, instantiate your new menu in the buildMenus() function
 * so that it will be in the allMenus array when the server starts.
 *
 * NOTE: You could customize a menu class by giving it its own nagivate()
 * function And then defining what tokens u want to use in there.
 *
 * NOTE: This class and its child classes are designed for dynamic binding. To
 * allow the session to "not care much" about the current menu it is in.
 *
 * NOTE: All client interactions with menus are done through const pointers.
 * It is very important that menus are read-only, as multiple
 * clients will be pointing to the same menu object at once.
 *
 * NOTE: All menus, when constructed, should initialize their own
 * header string. If not, they will use the default header (in Menu) which is
 * just a place holder.
 *
 */
class Menu
{
public:
   virtual int navigate(CommandTok* comm, Session* session) const;
   Menu();
   virtual MenuType getType() const;

protected:
   virtual int changeMenu(Session* session, MenuType menu) const;
   virtual int sendWelcome(Session* session) const;
   virtual int sendBadCommand(Session* session) const;

   virtual int badCommand(CommandTok* comm, Session* session) const;
   virtual int helpCommand(CommandTok* comm, Session* session) const;
   virtual int exitCommand(CommandTok* comm, Session* session) const;
   virtual int printCommand(CommandTok* comm, Session* session) const;
   virtual int backCommand(CommandTok* comm, Session* session) const;
   virtual int nameCommand(CommandTok* comm, Session* session) const;
   virtual int loginCommand(CommandTok* comm, Session* session) const;
   virtual int logoutCommand(CommandTok* comm, Session* session) const;
   virtual int signinCommand(CommandTok* comm, Session* session) const;
   virtual int makeAcctCommand(CommandTok* comm, Session* session) const;
   virtual int lBoardCommand(CommandTok* comm, Session* session) const;
   virtual int mainCommand(CommandTok* comm, Session* session) const;
   virtual int guestCommand(CommandTok* comm, Session* session) const;
   virtual int listCommand(CommandTok* comm, Session* session) const;
   virtual int joinCommand(CommandTok* comm, Session* session) const;
   virtual int dropPieceCommand(CommandTok* comm, Session* session) const;

   virtual int sendGlobalHelp(Session* session) const;

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
