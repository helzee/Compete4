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
// these make it easier to call for p1 or p2
#define PLAYER1 (Owner)1
#define PLAYER2 (Owner)2
// ----------------------------------------------------------------------------

using namespace std;

class GameSession
{
public:
   int gameID;
   int getNumPlayers() const;

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