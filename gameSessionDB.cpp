// Game Session Database is responsible for storing and directly creating all of
// the games that clients can connect to, as well as passing the clients through
// to gameSessions to be connected.

#include <pthread.h>
#include <vector>
#include "gameSessionDB.h"
#include "gameSession.h"

using namespace std;

/**
 * @brief This method allows the gameSession to simply create a new gameSession
 * object and append it to the back of the gameList that is eventually displayed
 * to the user when they want to display the list of available games.
 * 
 * @return int representing the size of the list of games 
 */
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

/**
 * @brief This method uses the inputted game id to collect the gameSession pointer
 * at that index within the list to hand it off to the calling client session.
 * 
 * @param id desired game id to collect pointer for
 * @return GameSession* pointer to the desired gameSession 
 */
GameSession* GameSessionDB::getGame(int id)
{
   if (id < gameList.size() && id >= 0) {
      return gameList[id];
   }

   return nullptr;
}

/**
 * @brief This method uses the getGame method to collect apointer to the desired game
 * using the passed id (client desired game #), and uses the gameSession method 
 * "connect player" to attatch the client session to the desired gameSession.
 * 
 * @param id desired game id #
 * @param session pointer to the requesting client session
 * @return true if session successfully connects to the gameSession
 * @return false if session is unsuccessful in it's connection attempt
 */
bool GameSessionDB::joinGame(int id, Session* session)
{
   GameSession* game = this->getGame(id);
   if (game == nullptr)
      return false;

   return game->connectPlayer(session);
}

/**
 * @brief This method is simmilar to the "joinGame" method, except instead of joining
 * a user specified game. The code looks for a game with one player already in the 
 * lobby waiting to start a game. If there are no games with one player already 
 * connected, then simply join the first empty game possible.
 * 
 * @param session pointer to the quick-joining client session
 * @return true if client is successfully placed into a gameSession
 * @return false if client is unable to be placed into a gameSession 
 */
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

/**
 * @brief Construct a new Game Session D B:: Game Session DB object, important to note
 * that the game automatically creates 10 gameSessions by default, allowing users to 
 * create more games in addition to this if needed.
 * 
 */
GameSessionDB::GameSessionDB()
{
   pthread_rwlock_init(&listLock, NULL);
   GameSession* temp;
   for (int i = 0; i < 10; i++) {
      temp = new GameSession(i);
      gameList.push_back(temp);
   }
}

/**
 * @brief This method walks through the available games and constructs a list of 
 * available games in the format of a string. This is used when the client requests to 
 * see the available games to join. The game ID is specified in the list.
 * 
 * @return string containing the list of gameSessions
 * 
 */
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