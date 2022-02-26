#include "gameSessionDB.h"
#include "gameSession.h"
#include <pthread.h>
#include <vector>
using namespace std;

// Create a new gamesession
// Add to the database/list
void GameSessionDB::makeGame() {}

// Hands off the gameSession object pointer to player's session
GameSession* GameSessionDB::getGame(int id)
{
   if (id < gameList.size()) {
      return gameList[id];
   }

   return nullptr;
}

bool GameSessionDB::removeGame(int id) { return false; }

GameSessionDB::GameSessionDB()
{
   pthread_rwlock_init(&listLock, NULL);
   gameCounter = 0;
}