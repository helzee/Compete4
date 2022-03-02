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
   gameCounter = 10;
   GameSession* temp;
   for (int i = 0; i < gameCounter; i++) {
      temp = new GameSession(i);
      gameList.push_back(temp);
   }
}

string GameSessionDB::gamesList() const
{
   string buffer = "Index\tPlayers\n";
   int gameID, playerCount;

   for (int i = 0; i < gameCounter; i++) {
      gameID = gameList[i]->gameID;
      playerCount = gameList[i]->getNumPlayers();
      buffer += to_string(gameID) + "\t" + to_string(playerCount) + "/2\n";
   }
   return buffer;
}