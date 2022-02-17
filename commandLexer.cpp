/**
 * @file commandLexer.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "commandLexer.h"
#include "constants.h"
#include <regex>
#include <string>
using namespace std;

// regex objects. icase = ignore case. match_continuous = only match from first
// char

CommandLexer::CommandLexer()
{
   regHelp = new regex(R"(^(help|h)\s)");
   regExit = new regex(R"(^(exit|quit|q)\s)");
   regPrint = new regex(R"(^(print|p)\s)");
   regBack = new regex(R"(^(back|b)\s)");
   regName = new regex(R"(^(name|n)\s)");
   regLogin = new regex(R"(^(login|l)\s)");
   regSignin = new regex(R"(^(signin|s)\s)");
   regMakeAcct = new regex(R"(^(m|makeaccount)\s)");
   regLBoard = new regex(R"(^(leaderboard|lb)\s)");
}

/**
 * @brief Scans a command sent by the user. Returns the command type as a token enum.
 * 
 * @param command the command sent by the user to be scanned
 * @return CommandTok : the token that this command represents (TOKBAD if the command does not exist)
 */
CommandTok CommandLexer::lexCommand(const char* command)
{
   const char *c = command;
   
   
   if (regex_search(c, *regHelp)) { //HELP
      return TOKHELP;
   } else if (regex_search(c, *regExit)) { //EXIT
      return TOKEXIT;
   } else if (regex_search(c, *regPrint)) { //PRINT
      return TOKPRINT;
   } else if (regex_search(c, *regBack)) { //BACK
      return TOKBACK;
   } else if (regex_search(c, *regLogin)) { //LOGIN
      return TOKLOGIN;
   } else if (regex_search(c, *regSignin)) { //SIGNIN
      return TOKSIGNIN;
   } else if (regex_search(c, *regMakeAcct)) { //MAKE ACCT
      return TOKMAKEACCT;
   } else if (regex_search(c, *regLBoard)) { //MAKE ACCT
      return TOKLBOARD;
   } 
   return TOKBAD;
}