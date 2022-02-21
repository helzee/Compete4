#include "../constants.h"

using namespace std;

class CommandTok;

/**
 * @brief Menu class (parent of all menus)
 * 
 */
class Menu {
public:
  int navigate(CommandTok* comm);
  Menu();

  private:
  enum MenuType { MENU = 0, MAIN, LOGIN, SIGNIN, MAKEACCOUNT, GUEST };

  MenuType type;
};

static Menu menu;
