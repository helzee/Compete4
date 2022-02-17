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

   regHelp = new regex(R"(^(h(elp)?)(\s))");
   regExit = new regex(R"(^(exit|q(uit)?)(\s))");
   regPrint = new regex(R"(^(p(rint)?)(\s))");
   regBack = new regex(R"(^(b(ack)?)(\s)*)");
   regName = new regex(R"(^(n(ame)?)(\s)*)");
   regLogin = new regex(R"(^(l(ogin)?)(\s)*)");
   regSignin = new regex(R"(^(s(ignin)?)(\s)*)");
   regMakeAcct = new regex(R"(^(m(akeaccount))(\s)*)");
   regLBoard = new regex(R"(^((lb)|(leaderboard))(\s)*)");
}

/**
 * @brief Scans a command sent by the user. Returns the command type as a token
 * enum.
 *
 * @param command the command sent by the user to be scanned
 * @return CommandTok : the token that this command represents (TOKBAD if the
 * command does not exist)
 */
CommandTok lexCommand(const char* command)
{
  

   if (regex_match(command, *regHelp)) { // HELP
      return TOKHELP;
   } else if (regex_match(command, *regExit)) { // EXIT
      return TOKEXIT;
   } else if (regex_match(command, *regPrint)) { // PRINT
      return TOKPRINT;
   } else if (regex_match(command, *regBack)) { // BACK
      return TOKBACK;
   } else if (regex_match(command, *regLBoard)) { // LEADERBOARD
      return TOKLBOARD;
   } else if (regex_match(command, *regLogin)) { // LOGIN
      return TOKLOGIN;
   } else if (regex_match(command, *regSignin)) { // SIGNIN
      return TOKSIGNIN;
   } else if (regex_match(command, *regMakeAcct)) { // MAKE ACCT
      return TOKMAKEACCT;

   } else if (regex_match(command, *regName)) { // NAME
      return TOKNAME;
   }

   return TOKBAD;
}