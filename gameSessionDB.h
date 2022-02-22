
#ifndef GAMESESSIONDB_H
#define GAMESESSIONDB_H
#include "constants.h"

class GameSession;

// Game List 
// When scalable, change to an odered map or vector
GameSession* gameList[MAX_GAMES];

// Create a new gamesession
// Add to the database/list
// When scalable, return gameSession* for users making games
void makeGame();

// When scalable add
// Ensure deletion of pointers/heap clear
/* bool removeGame(int);*/

// Hands off the gameSession object pointer to player's session
GameSession* getGame(int);

#endif