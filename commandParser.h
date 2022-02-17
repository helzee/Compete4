#include "commandLexer.h"
#include "constants.h"
#include "globalFuncs.h"
#include "loginCommands.h"
#include "session.h"

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

using namespace std;

const char* HELP_TEXT = "List of global commands:\n"
                        "help (h): self explanatory\n"
                        "exit (quit, q) : quit the game\n"
                        "leaderboard (lb) : view leaderboard\n"
                        "print (p) : re-print the current menu\n"
                        "name (n) : print your username\n";
const char* LBOARD_TEXT = "You are viewing the leaderboard\n";
const char* MAIN_MENU_HEADER = "------MAIN MENU------\n"
"login (l): to login or switch current acount\n";

bool parseCommand(string, Session*);
void mainMenuCommand(CommandTok, Session*);

#endif

/** Lex commands, return token (or return a false token)
 * each menu checkCommands(comand token, menu token) -> this function will
 * handle a command call based on the menu
 *
 *
 * menu function(string command)
 *    comTok = lexCommand
 *    if !checkForCommand(coTok, menu tok)
 *
 */