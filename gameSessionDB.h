
#ifndef GAMESESSIONDB_H
#define GAMESESSIONDB_H
#include "constants.h"
#include <pthread.h>
#include <vector>

class GameSession;

class GameSessionDB
{
public:
   GameSessionDB();
   GameSession* getGame(int);
   // Create a new gamesession
   // Add to the database/list
   // When scalable, return gameSession* for users making games
   void makeGame();

   // When scalable add
   // Ensure deletion of pointers/heap clear
   bool removeGame(int);

private:
   // Game List
   // When scalable, change to an odered map or vector
   vector<void*> gameList;
   int gameCounter;
   pthread_rwlock_t listLock;
};

#endif