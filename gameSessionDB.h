
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

   int makeGame();

   string gamesList() const;

private:
   vector<GameSession*> gameList;
   pthread_rwlock_t listLock;
};

#endif