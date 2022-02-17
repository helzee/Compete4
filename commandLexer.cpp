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

void initCommandLexer()
{
   
   regHelp = new regex(R"(^(help|h))");
   regExit = new regex(R"(^(exit|quit|q))");
   regPrint = new regex(R"(^(print|p))");
   regBack = new regex(R"(^(back|b))");
   regName = new regex(R"(^(name|n))");
   regLogin = new regex(R"(^(login|l))");
   regSignin = new regex(R"(^(signin|s))");
   regMakeAcct = new regex(R"(^(m|makeaccount))");
   regLBoard = new regex(R"(^(leaderboard|lb))");
}

/**
 * @brief Scans a command sent by the user. Returns the command type as a token enum.
 * 
 * @param command the command sent by the user to be scanned
 * @return CommandTok : the token that this command represents (TOKBAD if the command does not exist)
 */
CommandTok lexCommand(const char* command)
{
   const char *c = command;
   

   
   
   if (regex_search(c = command, *regHelp)) { // HELP
      return TOKHELP;
   } else if (regex_search(c = command, *regExit)) { // EXIT
      return TOKEXIT;
   } else if (regex_search(c = command, *regPrint)) { // PRINT
      return TOKPRINT;
   } else if (regex_search(c = command, *regBack)) { // BACK
      return TOKBACK;
   } else if (regex_search(c = command, *regLogin)) { // LOGIN
      return TOKLOGIN;
   } else if (regex_search(c = command, *regSignin)) { // SIGNIN
      return TOKSIGNIN;
   } else if (regex_search(c = command, *regMakeAcct)) { // MAKE ACCT
      return TOKMAKEACCT;
   } else if (regex_search(c = command, *regLBoard)) { // MAKE ACCT
      return TOKLBOARD;
   }
   
   return TOKBAD;
}