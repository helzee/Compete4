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
#include <string>
#include <regex>


#ifndef COMMANDLEXER_H
#define COMMANDLEXER_H








using namespace std;

class CommandLexer {
   private:
      static const regex* regHelp;
      static const regex* regExit;
      static const regex* regPrint;
      static const regex* regBack;
      static const regex* regName;
      static const regex* regLogin;
      static const regex* regSignin;
      static const regex* regMakeAcct;
      static const regex* regLBoard;

   public:
      CommandLexer();
      static CommandTok lexCommand(const char* command);
};



typedef enum CommandTok { 

   TOKBAD = 0,
   TOKHELP,
   TOKEXIT,    //quit or exit
   TOKPRINT,
   TOKBACK,
   TOKNAME,
   TOKLOGIN,
   TOKSIGNIN,
   TOKMAKEACCT,
   TOKLBOARD
   
 };



#endif