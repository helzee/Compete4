#include "constants.h"
#include "gameSession.h"
#ifndef GAMESESSIONDB_H
#define GAMESESSIONDB_H

// Game List
gameSession* gameList[MAX_GAMES];

// When scalable, return gameSession* for users making games
void makeGame();

// When scalable
//bool removeGame(int);

gameSession* getGame(int);

#endif