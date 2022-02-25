#include "commandParser.h"
#include "commandLexer.h"
#include "globalFuncs.h"
#include "session.h"

// Return false if the command was quit/exit
int parseCommand(string command, Session* session)
{

   // first step: check for global commands
   CommandTok* commTok = commandLexer.lexCommand(command.c_str());
   return session->handleCommand(commTok);
}