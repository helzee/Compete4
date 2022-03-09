#include "gameSession.h"
#include "board.h"
#include "session.h"
#include "userRecord.h"
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
   if (player->getRecord() == nullptr) {
      player->send("You cannot join a game without being signed in.");
      return false;
   }

   // read lock
   pthread_rwlock_rdlock(&lock);
   // if ingame, two players already connected
   if (inGame) {
      player->send("Error Connecting: Game is in Session\n");
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
      tryToStartGame();
      pthread_rwlock_unlock(&lock);

      return true;
   }
   // Check player two slot, if empty, add and set ingame to true
   if (players[1] == nullptr) {
      players[1] = player;
      player->setGame(this);
      player->send("Joining Game " + to_string(gameID) + " as player 1");
      // upon game-start, reset the game state
      tryToStartGame();
      pthread_rwlock_unlock(&lock);

      return true;
   }
   // in case session get past inGame and then preempted, unlock and exit
   // here.
   pthread_rwlock_unlock(&lock);
   player->send("\nError Connecting: Game Full\n");
   return false;
}

void GameSession::tryToStartGame()
{
   if (getNumPlayers() != 2 || inGame)
      return;

   inGame = true;
   resetBoard();
   announceUpdate();
}

void GameSession::announceUpdate() const
{
   string toAnnounce =
       "It is " + getCurTurnName() +
       "'s turn.\nPlease enter the column you'd like to drop into.\n";
   toAnnounce += printBoard();

   players[0]->send(toAnnounce);
   players[1]->send(toAnnounce);
}

string GameSession::getCurTurnName() const
{
   if (turn)
      return players[1]->getUserName();
   else
      return players[0]->getUserName();
}

bool GameSession::leaveLobby(Session* player)
{
   if (players[0] != nullptr) {
      if (players[0]->getSessionID() == player->getSessionID()) {
         // Player 0 leave
         players[0]->leaveGame(MAIN);
         players[0] = nullptr;
         return true;
      }
   }
   if (players[1] != nullptr) {
      if (players[1]->getSessionID() == player->getSessionID()) {
         // Player 1 leave
         players[1]->leaveGame(MAIN);
         players[1] = nullptr;
         return true;
      }
   }
   return false;
}

// Disconnect Player
bool GameSession::disconnectPlayer(Session* player)
{
   pthread_rwlock_wrlock(&lock);
   // If in the lobby, just let them quit, or if the other person left
   if (players[0] == nullptr || players[1] == nullptr || !inGame) {
      bool temp = leaveLobby(player);
      pthread_rwlock_unlock(&lock);
      return temp;
   }

   int thisPlayer, otherPlayer;
   if (players[0]->getSessionID() == player->getSessionID()) {
      thisPlayer = 0;
      otherPlayer = 1;
   } else if (players[1]->getSessionID() == player->getSessionID()) {
      thisPlayer = 1;
      otherPlayer = 0;
   } else {
      player->send("\nError Disconnecting: Not player not in target game\n");
      pthread_rwlock_unlock(&lock);
      return false;
   }

   if (!player->allowedToExit) {
      player->askToLeave();
      pthread_rwlock_unlock(&lock);
      return false;
   }

   // change commands menu for player from ingame to menu
   // disconnect players and player's current game

   players[thisPlayer]->getRecord()->loseGame();
   players[thisPlayer]->updateLB();
   players[thisPlayer]->leaveGame(MAIN);
   players[thisPlayer] = nullptr;

   if (players[otherPlayer] != nullptr) {
      players[otherPlayer]->send(
          "Other player has left the game, you win! Disconnecting you now.");

      players[otherPlayer]->getRecord()->winGame();
      players[otherPlayer]->updateLB();
      players[otherPlayer]->leaveGame(MAIN);
      players[otherPlayer] = nullptr;
   }

   inGame = false;
   player->send("\nSuccessfully disconnected from game\n");

   pthread_rwlock_unlock(&lock);
   return true;
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
bool GameSession::dropPiece(Session* player, int col)
{
   // OVERVIEW
   // ------------------------------------------
   // drop piece in board
   // check for win or tie
   // announce the winner/tie
   // update player records
   // change player menus
   // end by disconnecting users
   // ------------------------------------------

   // if (col > NUMCOLS || col <= 0) {
   //    player->send("Error: Invalid column number indicated to drop piece\n");
   //    return false;
   // }

   bool completed;

   Session* player1 = players[0];
   Session* player2 = players[1];
   // check for player number and if mutex (turn) is available
   if (player == player1 && turn == 0) {
      completed = board->dropPiece(col - 1, PLAYER1);
      if (board->getIsFinished()) {
         announceUpdate();
         announceWinner();
         return completed;
      }
      if (completed) {

         turn = 1;
      } else {
         player->send("Invalid move.");
      }

   }

   else if (player == player2 && turn == 1) {
      completed = board->dropPiece(col - 1, PLAYER2);
      if (board->getIsFinished()) {
         announceUpdate();
         announceWinner();
         return completed;
      }
      if (completed) {

         turn = 0;
      } else {
         player->send("Invalid move.");
      }
   }

   announceUpdate();
   return completed;
}

void GameSession::announceWinner()
{
   // end condition message
   string toAnnounce = "ERROR ENDING GAME";

   // winner, null if tie
   Owner winner = EMPTY;

   // records
   Record* p1 = players[0]->getRecord();
   Record* p2 = players[1]->getRecord();

   // determine winner or tie
   if (board->haveWinner())
      winner = board->getWinner();

   // Update winner records
   if (winner == PLAYER1) {
      // p1 win
      toAnnounce = "Game Over : P1 (" + getCurTurnName() + ") Wins!\n";
      p1->winGame();
      p2->loseGame();
   } else if (winner == PLAYER2) {
      // p2 win
      toAnnounce = "Game Over : P2 (" + getCurTurnName() + ") Wins!\n";
      p2->winGame();
      p1->loseGame();
   } else if (winner == EMPTY) {
      // tie
      toAnnounce = "Game Over : Game was a tie!\n";
      p1->tieGame();
      p2->tieGame();
   }

   players[0]->send(toAnnounce);
   players[1]->send(toAnnounce);

   // updates the leaderboards
   players[0]->updateLB();
   players[1]->updateLB();

   inGame = false;

   // Disconnect player, menu switched within method
   players[0]->leaveGame(MAIN);
   players[0] = nullptr;
   players[1]->leaveGame(MAIN);
   players[1] = nullptr;
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
string GameSession::printBoard() const { return board->print(); }

bool GameSession::chat(Session* player, string message)
{

   string toSend = "[" + player->getUserName() + "]: " + message.substr(1);

   // is sending player in the game?
   // is sender player one?
   if (player == players[0]) {
      // does game have a recipient?
      if (getNumPlayers() == 2) {
         players[1]->send(toSend);
         return true;
      }
   }

   // is sending player in the game?
   // is sender player two?
   else if (player == players[1]) {
      // does game have a recipient?
      if (getNumPlayers() == 2) {
         players[0]->send(toSend);
         return true;
      }
   }

   // if not full send message to player that game empty
   toSend = "Error: No Opponent In-Game\n";
   player->send(toSend);

   // necessary return value to session->ingamemenu
   return false;
}
