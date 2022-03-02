#include "gameSession.h"
#include "board.h"
#include "session.h"
#include <string>

// ----------------------------------------------------------------------------
//  Public Methods
// ----------------------------------------------------------------------------

// Constructor
GameSession::GameSession(int id)
{
   // Sets the fed gameid from gameDB into this game's identifier
   inGame = false;
   turn = false;
   gameID = id;
   board = new Board();

   // Setting the players to empty
   players[0] = nullptr;
   players[1] = nullptr;

   pthread_rwlock_init(&lock, NULL);
}

int GameSession::getNumPlayers() const
{
   return ((players[0] != nullptr) ? 1 : 0) + ((players[1] != nullptr) ? 1 : 0);
}

// Connect Player
bool GameSession::connectPlayer(Session* player)
{
   // read lock
   pthread_rwlock_rdlock(&lock);
   // if ingame, two players already connected
   if (inGame) {
      player->send("Error Connecting: Game Full");
      pthread_rwlock_unlock(&lock);
      return false;
   }
   pthread_rwlock_unlock(&lock);
   // unlock read, lock write
   pthread_rwlock_wrlock(&lock);
   // Check player one slot
   if (players[0] == nullptr) {
      players[0] = player;
      player->setGame(this);
      player->send("Joining Game " + to_string(gameID) + " as player 0");
      pthread_rwlock_unlock(&lock);
      return true;
   }
   // Check player two slot, if empty, add and set ingame to true
   if (players[1] == nullptr) {
      players[1] = player;
      player->setGame(this);
      player->send("Joining Game " + to_string(gameID) + " as player 1");
      inGame = true;
      pthread_rwlock_unlock(&lock);
      // upon game-start, reset the game state
      resetBoard();
      return true;
   }
   // in case session get past inGame and then preempted, unlock and exit
   // here.
   pthread_rwlock_unlock(&lock);
   player->send("Error Connecting: Game Full");
   return false;
}

// Disconnect Player
bool GameSession::disconnectPlayer(Session* player)
{
   // doesn't matter if ingame
   // check player one
   // locked for writing
   pthread_rwlock_wrlock(&lock);
   if (players[0]->getSessionID() == player->getSessionID()) {

      // disconnect players and player's current game
      player->setGame(nullptr);
      players[0] == nullptr;
      pthread_rwlock_unlock(&lock);
      player->send("Successfully disconnected from game");
      return true;
   }
   // check player two
   else if (players[1]->getSessionID() == player->getSessionID()) {

      // disconnect players and player's current game
      player->setGame(nullptr);
      players[1] == nullptr;
      pthread_rwlock_unlock(&lock);
      player->send("Successfully disconnected from game");
      return true;
   }
   pthread_rwlock_unlock(&lock);
   player->send("Error Disconnecting: Not player not in target game");
   return false;
}

// Resets board when both players have connected to the game
void GameSession::resetBoard() { board->reset(); }

// Drop piece
// This method is the core of the game
// It is responsible for:
//  1. Dropping pieces into directed column
//  2. Checking for wincondition
//  2b.      announce win
//  2c.      terminate game (disconnect players), set inGame
//  3. Switch turns
//  4. Print out board
/**
 * @brief
 *
 * NOTE: This function is hard to predict, as we have not planned out what
 * the menu for the game session will look like yet. if this function is
 * responsible for dropping a piece, it may be called multiple times (if
 * improper rows are given) so we have to be ready to call this function again
 * and again from the same player before changing the turn or checking for wins
 * or printing the board. -Josh
 *
 * NOTE: I changed return to int as this function
 * may return different ints based on wheter drop piece was successful or not OR
 * a win happened.
 *
 * @param player
 * @param row
 * @return int
 */
int GameSession::dropPiece(Session* player, int row)
{
   // INCOMPLETE!
   Session* player1 = players[0];
   Session* player2 = players[1];
   // check for player number and if mutex (turn) is available
   if (player == player1 && turn == 0) {
      board->dropPiece(row, PLAYER1);
   } else if (player == player2 && turn == 1) {
      board->dropPiece(row, PLAYER2);
   }

   return 0;
}

// Print Board
// prints out the matrix that represents the connect 4 board
// ASCII border around characters and within frame to make state clear
/*
    Example string:
    |_._._._._._._|
    | T T T T T T |
    | T T T T T T |
    | T T T T T T |
    | T T TxT T T |
    | T ToToT T T |
    | TxTxToT T T |
    /‾‾‾‾‾‾‾‾‾‾‾‾‾/
*/
string GameSession::printBoard() { return board->print(); }

// ----------------------------------------------------------------------------
//  Private Methods
// ----------------------------------------------------------------------------

// Part of game
// Determines if session attempting to change the gamestate is an active player
// within the game
bool GameSession::partOfGame(Session* sender)
{
   // Check players one and two
   pthread_rwlock_rdlock(&lock);
   if (players[0]->getSessionID() == sender->getSessionID()) {
      pthread_rwlock_unlock(&lock);
      return true;
   } else if (players[1]->getSessionID() == sender->getSessionID()) {
      pthread_rwlock_unlock(&lock);
      return true;
   }
   pthread_rwlock_unlock(&lock);
   return false;
}

// Determines if the player sending information is allowed to move
// Helper used in droppiece
bool GameSession::isTurn(Session* player)
{
   // Determine if player is p1 or p2 slot
   // Compare with turn boolean: false = p1, true = p2
   if (players[0]->getSessionID() == player->getSessionID()) {
      if (!isTurn(player)) {
         return true;
      }

   } else if (players[1]->getSessionID() == player->getSessionID()) {
      return true;
   }
   return false;
}

// Checks for the win condition
// Used after every droppiece so if connect four is achieved, the game is over
bool GameSession::checkWin() { return false; }

// Announce Update
// Print out board after a move is made to both players
// When game is completed, announce the winnder to both players
// TBD