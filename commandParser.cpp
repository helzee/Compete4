// Parse command is repsonsible for serveing as an intermediary between 
// determining the correct token associated with the client sent and 
// sending it to the client's session to be handled and executed.

#include "commandParser.h"
#include "commandLexer.h"
#include "globalFuncs.h"
#include "session.h"

/**
 * @brief Parse command is the sole function of the command parser. 
 * It simply uses the provided commandLexer to collect the right token
 * to send to the session's command handler.
 * 
 * @param command literal command string recieved from client
 * @param session pointer to the client session
 * @return int marker indicating parse success
 */
int parseCommand(string command, Session* session)
{

   // first step: check for global commands
   CommandTok* commTok = commandLexer.lexCommand(command.c_str());
   return session->handleCommand(commTok);
}