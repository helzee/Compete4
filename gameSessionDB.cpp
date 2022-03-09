#include "gameSessionDB.h"
#include "gameSession.h"
#include <pthread.h>
#include <vector>
using namespace std;

// Create a new gamesession
// Add to the database/list
int GameSessionDB::makeGame()
{
   int newGame = -1;

   pthread_rwlock_wrlock(&listLock);
   if (gameList.size() < MAXGAMES) {
      newGame = gameList.size();
      gameList.push_back(new GameSession(newGame));
   }
   pthread_rwlock_unlock(&listLock);

   return newGame;
}

// Hands off the gameSession object pointer to player's session
GameSession* GameSessionDB::getGame(int id)
{
   if (id < gameList.size() && id >= 0) {
      return gameList[id];
   }

   return nullptr;
}

bool GameSessionDB::joinGame(int id, Session* session)
{
   GameSession* game = this->getGame(id);
   if (game == nullptr)
      return false;

   return game->connectPlayer(session);
}

bool GameSessionDB::removeGame(int id) { return false; }

GameSessionDB::GameSessionDB()
{
   pthread_rwlock_init(&listLock, NULL);
   GameSession* temp;
   for (int i = 0; i < 10; i++) {
      temp = new GameSession(i);
      gameList.push_back(temp);
   }
}

string GameSessionDB::gamesList() const
{
   string buffer = "Index\tPlayers\n";
   int gameID, playerCount;

   for (int i = 0; i < gameList.size(); i++) {
      playerCount = gameList[i]->getNumPlayers();

      if (playerCount < 2) {
         gameID = gameList[i]->gameID;
         buffer += to_string(gameID) + "\t" + to_string(playerCount) + "/2\n";
      }
   }
   return buffer;
}