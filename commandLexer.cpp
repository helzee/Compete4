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

// REGEX strings split into prefix - regex - suffix
// These strings auto concat at runtime
#define REGPREFIX "(^"
#define REGSUFFIX "(\\s)*)"

#define REGHELP "(h(elp)?)"
#define REGEXIT "(exit|(q(uit)?))"
#define REGPRINT "(p(rint)?)"
#define REGBACK "(b(ack)?)"
#define REGNAME "(n(ame)?)"
#define REGLOGIN "(l(ogin)?)"
#define REGLBOARD "(leaderboard|lb)"
#define REGSIGNIN "(s(ignin)?)"
#define REGMAKEACCT "(m(akeaccount)?)"

#include "commandLexer.h"
#include "constants.h"
#include <regex>
#include <string>
using namespace std;

// regex objects. icase = ignore case. match_continuous = only match from first
// char

void initCommandLexer()
{
   regHelp = new regex(REGPREFIX REGHELP REGSUFFIX);
   regExit = new regex(REGPREFIX REGEXIT REGSUFFIX);
   regPrint = new regex(REGPREFIX REGPRINT REGSUFFIX);
   regBack = new regex(REGPREFIX REGBACK REGSUFFIX);
   regName = new regex(REGPREFIX REGNAME REGSUFFIX);
   regLogin = new regex(REGPREFIX REGLOGIN REGSUFFIX);
   regSignin = new regex(REGPREFIX REGSIGNIN REGSUFFIX);
   regMakeAcct = new regex(REGPREFIX REGMAKEACCT REGSUFFIX);
   regLBoard = new regex(REGPREFIX REGLBOARD REGSUFFIX);

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