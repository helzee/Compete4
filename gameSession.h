/** @file gameSession.h
 *
 */

#ifndef GAMESESSION_H
#define GAMESESSION_H

#include "constants.h"
#include <pthread.h>

#include "globalFuncs.h"

class Session;
class Board;

// gameSession constants
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

using namespace std;

class GameSession
{
public:
   int gameID;

   bool connectPlayer(Session*);
   bool disconnectPlayer(Session*);
   void resetBoard();

   int dropPiece(Session*, int);
   string printBoard();

   GameSession(int);

private:
   Session* players[2];

   Board* board;
   bool turn;
   bool inGame;

   bool partOfGame(Session*);
   bool isTurn(Session*);
   bool checkWin();
   void announceUpdate();
   pthread_rwlock_t lock;
};

#endif