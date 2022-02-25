#include "gameSession.h"
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
   // Initialize the board with empty spaces
   // Set the number of tokens in each column to 0
   // Player one will use: x
   // Player two will use: o
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         board[i][j] = ' ';
         // # of tokens in each col
         colCount[j] = 0;
      }
   }

   // Setting the players to empty
   players[0] = nullptr;
   players[1] = nullptr;

   pthread_rwlock_init(&lock, NULL);
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
   if (players[0] != nullptr) {
      players[0] == player;
      player->setGame(this);
      pthread_rwlock_unlock(&lock);
      return true;
   }
   // Check player two slot, if empty, add and set ingame to true
   if (players[1] != nullptr) {
      players[1] == player;
      player->setGame(this);
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
// Check connnectPlayer
void GameSession::resetBoard()
{
   // Set the number of tokens in each column to 0
   // Player one will use: x
   // Player two will use: o
   pthread_rwlock_wrlock(&lock);
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         board[i][j] = ' ';
         // # of tokens in each col
         colCount[j] = 0;
      }
   }
   pthread_rwlock_unlock(&lock);
}

// Drop piece
// This method is the core of the game
// It is responsible for:
//  1. Dropping pieces into directed column
//  2. Checking for wincondition
//  2b.      announce win
//  2c.      terminate game (disconnect players), set inGame
//  3. Switch turns
//  4. Print out board

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
string GameSession::printBoard()
{
   string connectBoard = "";
   // Print Board Top
   connectBoard += "|_._._._._._._|\n";
   // Board print per row
   // prints out 2x colnum characters
   for (int i = 0; i < BOARD_ROW; i++) {
      connectBoard += "|";
      for (int j = 0; j < (BOARD_COL * 2) - 1; j++) {
         // is a seperator char
         if (i % 2 == 0) {
            connectBoard += "T";
         }
         // is a token slot
         else {
            connectBoard += board[i][j - (j / 2)];
         }
      }
      connectBoard += "|\n";
   }
   // Print Board Base
   connectBoard += "/‾‾‾‾‾‾‾‾‾‾‾‾‾/\n";

   return connectBoard;
}

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
   }
   else if (players[1]->getSessionID() == sender->getSessionID()) {
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
}

// Checks for the win condition
// Used after every droppiece so if connect four is achieved, the game is over
bool checkWin()
{
   // horizontal
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         // check player1
         if (board[i][j] == 'o' && board[i][j + 1] == 'o' &&
             board[i][j + 2] == 'o' && board[i][j + 3] == 'o' &&) {
            return true;
         }
         // check player2
         if (board[i][j] == 'x' && board[i][j + 1] == 'x' &&
             board[i][j + 2] == 'x' && board[i][j + 3] == 'x' &&) {
            return true;
         }
      }
   }
   // vertical
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         // check player1
         if (board[i][j] == 'o' && board[i + 1][j] == 'o' &&
             board[i + 2][j] == 'o' && board[i + 3][j] == 'o' &&) {
            return true;
         }
         // check player2
         if (board[i][j] == 'x' && board[i + 1][j] == 'x' &&
             board[i + 1][j] == 'x' && board[i + 1][j] == 'x' &&) {
            return true;
         }
      }
   }
   // descending diagonal
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         // check player1
         if (board[i][j] == 'o' && board[i - 1][j - 1] == 'o' &&
             board[i - 2][j - 2] == 'o' && board[i - 3][j - 3] == 'o' &&) {
            return true;
         }
         // check player2
         if (board[i][j] == 'x' && board[i - 1][j - 1] == 'x' &&
             board[i - 2][j - 2] == 'x' && board[i - 3][j - 3] == 'x' &&) {
            return true;
         }
      }
   }
   // ascending diagonal
   for (int i = 0; i < BOARD_ROW; i++) {
      for (int j = 0; j < BOARD_COL; j++) {
         // check player1
         if (board[i][j] == 'o' && board[i - 1][j + 1] == 'o' &&
             board[i - 2][j + 2] == 'o' && board[i - 3][j + 3] == 'o' &&) {
            return true;
         }
         // check player2
         if (board[i][j] == 'x' && board[i - 1][j + 1] == 'x' &&
             board[i - 2][j + 2] == 'x' && board[i - 3][j + 3] == 'x' &&) {
            return true;
         }
      }
   }
   return false;
}

// Announce Update
// Print out board after a move is made to both players
// When game is completed, announce the winnder to both players
// TBD