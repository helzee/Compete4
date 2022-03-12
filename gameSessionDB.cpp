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

bool GameSessionDB::quickJoin(Session* session)
{
   GameSession* game;

   // Try to join a game with 1 player
   for (int i = 0; i < gameList.size(); i++) {
      game = this->getGame(i);
      if (game == nullptr)
         continue;

      if (game->getNumPlayers() == 1)
         break;
      if (game->connectPlayer(session))
         return true;
   }

   // Try to join an empty game if it fails
   for (int i = 0; i < gameList.size(); i++) {
      game = this->getGame(i);
      if (game == nullptr)
         continue;

      if (game->getNumPlayers() == 0)
         break;
      if (game->connectPlayer(session))
         return true;
   }

   // Try to make a new game
   int newGame = makeGame();
   if (newGame != -1)
      return joinGame(newGame, session);

   // Every game was full, and no more games can be made
   return 1;
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