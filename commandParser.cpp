#include "commandParser.h"
#include "commandLexer.h"
#include "constants.h"
#include "globalFuncs.h"
#include "session.h"
#include "constants.h"

// helper strings


// Return false if the command was quit/exit
bool parseCommand(string command, Session* session)
{
   // lexer needs newline to work
   string newLineComm = command + "\n";
   // first step: check for global commands
   CommandTok* commTok = commandLexer.lexCommand(newLineComm.c_str());
   return session->handleCommand(commTok);
   
}