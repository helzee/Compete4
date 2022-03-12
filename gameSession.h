/** @file gameSession.h
 *
 */

#ifndef GAMESESSION_H
#define GAMESESSION_H

#include <pthread.h>
#include "constants.h"
#include "globalFuncs.h"

#define PLAYER1 (Owner)1
#define PLAYER2 (Owner)2

class Session;
class Board;

using namespace std;

class GameSession
{
public:
   int gameID;

   GameSession(int);   
   int getNumPlayers() const;
   bool connectPlayer(Session*);
   bool disconnectPlayer(Session*);
   bool dropPiece(Session*, int);
   bool chat(Session*, string);
   bool leaveLobby(Session*);
   string printBoard() const;
   void resetBoard();

private:
   Session* players[2];
   Board* board;
   
   bool turn;
   bool inGame;

   void tryToStartGame();
   void announceWinner();
   void announceUpdate() const;
   string getCurTurnName() const;

   pthread_rwlock_t lock;
};

#endif