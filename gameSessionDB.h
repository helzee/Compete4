#include "constants.h"
#include "gameSession.h"
#ifndef GAMESESSIONDB_H
#define GAMESESSIONDB_H

// Game List 
// When scalable, change to an odered map or vector
gameSession* gameList[MAX_GAMES];

// Create a new gamesession
// Add to the database/list
// When scalable, return gameSession* for users making games
void makeGame();

// When scalable add
// Ensure deletion of pointers/heap clear
/* bool removeGame(int);*/

// Hands off the gameSession object pointer to player's session
gameSession* getGame(int);

#endif