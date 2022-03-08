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
   regHelp = new regex(REGPREFIX REGHELP REGSUFFIX);
   regExit = new regex(REGPREFIX REGEXIT REGSUFFIX);
   regPrint = new regex(REGPREFIX REGPRINT REGSUFFIX);
   regBack = new regex(REGPREFIX REGBACK REGSUFFIX);
   regName = new regex(REGPREFIX REGNAME REGSUFFIX);
   regLogin = new regex(REGPREFIX REGLOGIN REGSUFFIX);
   regLogout = new regex(REGPREFIX REGLOGOUT REGSUFFIX);
   regSignin = new regex(REGPREFIX REGSIGNIN REGSUFFIX);
   regMakeAcct = new regex(REGPREFIX REGMAKEACCT REGSUFFIX);
   regLBoard = new regex(REGPREFIX REGLBOARD REGSUFFIX);
   regMain = new regex(REGPREFIX REGMAIN REGSUFFIX);
   regGuest = new regex(REGPREFIX REGGUEST REGSUFFIX);
   regList = new regex(REGPREFIX REGLIST REGSUFFIX);
   regJoin = new regex(REGPREFIX REGJOIN REGSUFFIX);
   regDP = new regex(REGPREFIX REGDP REGSUFFIX);
   regChat = new regex(REGPREFIX REGCHAT REGSUFFIX);
}

/**
 * @brief Scans a command sent by the user. Returns the command type as a token
 * enum. Future idea: We could pass in the current menu if we wanted to create
 * unique tokens for each menu.
 *
 * @param command the command sent by the user to be scanned
 * @return CommandTok : the token that this command represents (TOKBAD if the
 * command does not exist)
 */
CommandTok* CommandLexer::lexCommand(string command) const
{
   CommandTok* tok = new CommandTok();
   tok->type = determineTok(command);
   tok->lex = command.substr(0, command.size() - 1);
   return tok;
}
CommandTok::CommandTok()
{
   type = TOKBAD;
   lex = "";
}

TokType CommandTok::getType() const { return type; }
string CommandTok::getLex() const { return lex; }

TokType CommandLexer::determineTok(string command) const
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
   } else if (regex_match(command, *regLogout)) { // LOGOUT
      return TOKLOGOUT;
   } else if (regex_match(command, *regSignin)) { // SIGNIN
      return TOKSIGNIN;
   } else if (regex_match(command, *regMakeAcct)) { // MAKE ACCT
      return TOKMAKEACCT;

   } else if (regex_match(command, *regName)) { // NAME
      return TOKNAME;
   } else if (regex_match(command, *regMain)) { // MAIN
      return TOKMAIN;
   } else if (regex_match(command, *regGuest)) { // GUEST
      return TOKGUEST;
   } else if (regex_match(command, *regList)) { // LIST
      return TOKLIST;
   } else if (regex_match(command, *regJoin)) { // JOIN
      return TOKJOIN;
   }

   else if (regex_match(command, *regDP)) // DROP PIECE
   {
      return TOKDP;
   }
   else if (regex_match(command, *regChat))
   {
      return TOKCHAT;
   }

   return TOKBAD;
}