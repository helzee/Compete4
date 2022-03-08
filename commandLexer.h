/**
 * @file commandLexer.h
 * @author
 * @brief
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "constants.h"
#include <regex>
#include <string>

#ifndef COMMANDLEXER_H
#define COMMANDLEXER_H

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
#define REGLOGOUT "(lo(gout)?)"
#define REGLBOARD "(leaderboard|lb)"
#define REGSIGNIN "(s(ignin)?)"
#define REGMAKEACCT "(m(akeaccount)?)"
#define REGMAIN "(main)"
#define REGGUEST "(g(uest)?)"
#define REGLIST "((list)|(ls))"
#define REGJOIN "(j(oin)? [[:digit:]]+)"
#define REGDP "([[:digit:]]+)"
#define REGCHAT "(>[[:print:]]*)"

using namespace std;

enum TokType {

   TOKBAD = 0,
   TOKHELP,
   TOKEXIT, // quit or exit
   TOKPRINT,
   TOKBACK,
   TOKNAME,
   TOKLOGIN,
   TOKLOGOUT,
   TOKSIGNIN,
   TOKMAKEACCT,
   TOKLBOARD,
   TOKMAIN,
   TOKGUEST,
   TOKLIST,
   TOKJOIN,
   TOKDP,
   TOKCHAT,
};

class CommandTok
{
   friend class CommandLexer;

public:
   CommandTok();
   TokType getType() const;
   string getLex() const;

private:
   TokType type;
   string lex;
};

/** NOTE: CommandLexer is meant to be used as a static class! It is instantiated
 * at the bottom of this header.
 *
 * NOTE: How to add new commands:
 *
 * 1) define new regex definition (at the top of this header)
 *
 * 2) define a new command TokType (above this comment in the enum)
 *
 * 3) declare a new regex* (in the private section of CommandLexer)
 *
 * 4) instantiate the new regex in CommandLexer constructor (.cpp)
 *
 * 5) in .cpp, add a new "else if regex match" statement that returns
 * your new command tokType in determineTok()
 *
 * 6) update the Menu::navigate() function to have a new case that recognizes
 * your token Then, be sure to implement the command's function in he menu you
 * want it to be used.
 *
 * The command lexer can also be seen as a builder of CommandToks*/

class CommandLexer
{
public:
   CommandLexer();
   CommandTok* lexCommand(string command) const;

private:
   regex* regHelp;
   regex* regExit;
   regex* regPrint;
   regex* regBack;
   regex* regName;
   regex* regLogin;
   regex* regLogout;
   regex* regSignin;
   regex* regMakeAcct;
   regex* regLBoard;
   regex* regMain;
   regex* regGuest;
   regex* regList;
   regex* regJoin;

   regex* regDP;
   regex* regChat;

   TokType determineTok(string command) const;
};

static const CommandLexer commandLexer;

#endif