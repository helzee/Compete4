
#ifndef GAMESESSIONDB_H
#define GAMESESSIONDB_H
#include "constants.h"
#include <pthread.h>
#include <vector>

#define MAXGAMES 30

using namespace std;
class GameSession;

class GameSessionDB
{
public:
   GameSessionDB();
   GameSession* getGame(int);

   bool joinGame(int, Session*);
   bool quickJoin(Session*);

   // Create a new gamesession
   // Add to the database/list
   // When scalable, return gameSession* for users making games
   int makeGame();

   // When scalable add
   // Ensure deletion of pointers/heap clear
   bool removeGame(int);

   string gamesList() const;

private:
   // Game List
   // When scalable, change to an odered map or vector
   vector<GameSession*> gameList;
   pthread_rwlock_t listLock;
};

#endif