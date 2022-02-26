#include "gameSessionDB.h"
#include "gameSession.h"
#include <vector>
using namespace std;

// Create a new gamesession
// Add to the database/list
void GameSessionDB::makeGame() {}

// Hands off the gameSession object pointer to player's session
GameSession* GameSessionDB::getGame(int id)
{
   if (id < gameList.size()) {
      return (GameSession*)gameList[id];
   }

   return nullptr;
}