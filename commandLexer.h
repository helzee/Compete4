/**
 * @file commandLexer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-02-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "constants.h"
#include <regex>

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
#define REGLBOARD "(leaderboard|lb)"
#define REGSIGNIN "(s(ignin)?)"
#define REGMAKEACCT "(m(akeaccount)?)"
#define REGMAIN "(main)"
#define REGGUEST "(g(uest)?)"

using namespace std;

enum TokType {

   TOKBAD = 0,
   TOKHELP,
   TOKEXIT, // quit or exit
   TOKPRINT,
   TOKBACK,
   TOKNAME,
   TOKLOGIN,
   TOKSIGNIN,
   TOKMAKEACCT,
   TOKLBOARD,
   TOKMAIN,
   TOKGUEST

};

class CommandTok
{
   friend class CommandLexer;

public:
   CommandTok();
   TokType getType() const;
   const char* getLex() const;

private:
   TokType type;
   const char* lex;
};

/** NOTE: CommandLexer is meant to be used as a static class! It is instantiated
 * at the bottom of this header.
 *
 * The command lexer can also be seen as a builder of CommandToks*/

class CommandLexer
{
public:
   CommandLexer();
   CommandTok* lexCommand(const char* command) const;

private:
   regex* regHelp;
   regex* regExit;
   regex* regPrint;
   regex* regBack;
   regex* regName;
   regex* regLogin;
   regex* regSignin;
   regex* regMakeAcct;
   regex* regLBoard;
   regex* regMain;
   regex* regGuest;

   TokType determineTok(const char* command) const;
};

static const CommandLexer commandLexer;

#endif