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

using namespace std;

enum CommandTok {

   TOKBAD = 0,
   TOKHELP,
   TOKEXIT, // quit or exit
   TOKPRINT,
   TOKBACK,
   TOKNAME,
   TOKLOGIN,
   TOKSIGNIN,
   TOKMAKEACCT,
   TOKLBOARD

};

static regex* regHelp;
static regex* regExit;
static regex* regPrint;
static regex* regBack;
static regex* regName;
static regex* regLogin;
static regex* regSignin;
static regex* regMakeAcct;
static regex* regLBoard;

void initCommandLexer();

CommandTok lexCommand(const char* command);


#endif