// Game Session functions primarily as the "lobby" of the game. The lobby is
// simply an interface between the gamestate and the client sessions This means
// that interact with it. Therefore GameSession handles much of the network 
// procedure for the functions of the game lobby: connecting, disconnecting, 
// back-end updates, etc. 

#include <string>
#include "gameSession.h"
#include "board.h"
#include "session.h"
#include "userRecord.h"

// ----------------------------------------------------------------------------
//  Public Methods
// ----------------------------------------------------------------------------

/**
 * @brief Construct a new Game Session:: Game Session object and initialize all 
 * of the members of the gamesession. Player-slots are empty by default and a
 * new board object that tracks the state of this gameSession is created.
 * 
 * @param id The assigned game id sent from gameSessionDB
 */
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

/**
 * @brief Get num players is a method that quickly determines the number of 
 * players in the game and sends it to the calling function. It does this by
 * quickly counting based on the state of the playerslots that gameSession 
 * stores.
 * 
 * @return int number of players in the current gameSession
 */
int GameSession::getNumPlayers() const
{
   return ((players[0] != nullptr) ? 1 : 0) + ((players[1] != nullptr) ? 1 : 0);
}

/**
 * @brief Connect player does what it's named. It is fed a pointer to the 
 * session attempting to connect to this particular instance of gameSession
 * and it (safely, using locks) connects the incoming player to the first 
 * available player slot in the game. If both player slots are full and/or
 * the flag inGame is set, the incoming request to join is rejected and a 
 * failure message is sent to the player attempting to connect. Incoming 
 * players without a player-record are also rejected. Each time a player is
 * successfully a check to start the game is made, if successful the game
 * begins.
 * 
 * @param player pointer to incoming player session
 * @return true if player is connected
 * @return false if player unable to connect
 */
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
      player->send("Joining Game " + to_string(gameID) + " as player 1");

      tryToStartGame();
      pthread_rwlock_unlock(&lock);
      return true;
   }
   // Check player two slot, if empty, add and set ingame to true
   if (players[1] == nullptr) {
      players[1] = player;
      player->setGame(this);
      player->send("Joining Game " + to_string(gameID) + " as player 2");

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

/**
 * @brief The leaveLobby method allows sessions in a game that hasn't started
 * to gracefully disconnect from the lobby they are connected to.
 * 
 * @param player session attempting to back
 * @return true if successful
 * @return false if unsuccessful
 */
bool GameSession::leaveLobby(Session* player)
{
   if (players[0] != nullptr) {
      if (players[0]->getSessionID() == player->getSessionID()) {
         players[0]->leaveGame(MAIN);
         players[0] = nullptr;
         return true;
      }
   }
   if (players[1] != nullptr) {
      if (players[1]->getSessionID() == player->getSessionID()) {
         players[1]->leaveGame(MAIN);
         players[1] = nullptr;
         return true;
      }
   }
   return false;
}

/**
 * @brief Disconnect player is a method used when a player is needed to be 
 * removed from the game. In addition to clearing the target player from the
 * player slots, this method also updates records of the disconnecting player
 * as well as the remaining player (as a wincondition has been satisfied). 
 * Due to the game being complete once someone leaves. The remaining player is
 * also removed from the current game. A method called in each of the sessions
 * disconnects it from the game on it's own end, and both sessions are removed
 * from the player slots. Once all of this is done, the leaderboard is updated.
 * 
 * @param player 
 * @return true 
 * @return false 
 */
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
      players[otherPlayer]->send("Other player has left the game, meaning you "
                                 "win! Disconnecting you now.");

      players[otherPlayer]->getRecord()->winGame();
      players[otherPlayer]->updateLB();
      players[otherPlayer]->leaveGame(MAIN);
      players[otherPlayer] = nullptr;
   }

   inGame = false;
   pthread_rwlock_unlock(&lock);

   player->send("\nSuccessfully disconnected from game\n");
   return true;
}

// calls the board's reset function
void GameSession::resetBoard() { board->reset(); }

/**
 * @brief
 * 
 * Drop piece
 * This method is the core of the game
 * It is responsible for:
 *  1. Dropping pieces into desired column
 *  2. Checking for wincondition
 *  2b.      announce win
 *  2c.      terminate game 
 *  3. Switch turns
 *  4. Announce the updated board
 *
 * @param player
 * @param row
 * @return int
 */
bool GameSession::dropPiece(Session* player, int col)
{
   if (!inGame) {
      player->send("Please wait for the game to start.");
      return false;
   }

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

// if in a game calls the board's print method and returns the board's string
string GameSession::printBoard() const
{
   if (!inGame)
      return "The game has not started.";
   return board->print();
}

/**
 * @brief Chat is a method that uses the information stored in the gameSession
 * to take a message provided by a requesting clientsession and sends it to their
 * opponent, if there is one, in the game. The method appends the senders name
 * to the message before sending.
 * 
 * @param player pointer to the session sending the chat message
 * @param message the message to be sent
 * @return true if chat sent successfully
 * @return false if chat not sent
 */
bool GameSession::chat(Session* player, string message)
{
   if (!inGame) {
      player->send("The game has not started.");
      return false;
   }

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

// ----------------------------------------------------------------------------
//  Private  Methods
// ----------------------------------------------------------------------------

/**
 * @brief This method attempts to start a game, and is called within connectPlayer
 * it simply makes sure that two players are connected to the game. It then clears
 * the board to make it new for the players and announces an update.
 * 
 */
void GameSession::tryToStartGame()
{
   if (getNumPlayers() != 2 || inGame)
      return;

   inGame = true;
   resetBoard();
   announceUpdate();
}

/**
 * @brief This method is called once the game determines if the win-condition is
 * is satisfied in dropPiece. It sends out the end of game message to both players,
 * updates their records, and updates the leaderboard.
 * 
 */
void GameSession::announceWinner()
{
   // end condition message
   string toAnnounce = "ERROR ENDING GAME";

   // winner, null if tie
   Owner winner = EMPTY;

   pthread_rwlock_wrlock(&lock);

   // records
   Record* p1 = players[0]->getRecord();
   Record* p2 = players[1]->getRecord();

   // determine winner or tie
   if (board->haveWinner())
      winner = board->getWinner();

   // Update winner records
   if (winner == PLAYER1) {
      toAnnounce = "Game Over : P1 (" + getCurTurnName() + ") Wins!\n";
      p1->winGame();
      p2->loseGame();
   } else if (winner == PLAYER2) {
      toAnnounce = "Game Over : P2 (" + getCurTurnName() + ") Wins!\n";
      p2->winGame();
      p1->loseGame();
   } else if (winner == EMPTY) {
      toAnnounce = "Game Over : Game was a tie!\n";
      p1->tieGame();
      p2->tieGame();
   }

   players[0]->send(toAnnounce);
   players[1]->send(toAnnounce);

   players[0]->updateLB();
   players[1]->updateLB();

   pthread_rwlock_unlock(&lock);

   inGame = false;

   // Disconnect player, menu switched within method
   players[0]->leaveGame(MAIN);
   players[0] = nullptr;
   players[1]->leaveGame(MAIN);
   players[1] = nullptr;
}

/**
 * @brief Sends out a message containing who's turn it is to drop a piece, and an
 * ascii representaiton of the gamestate to both players with a message prompting
 * a move.
 * 
 */
void GameSession::announceUpdate() const
{
   string toAnnounce =
       "It is " + getCurTurnName() +
       "'s turn.\nPlease enter the column you'd like to drop into.\n";
   toAnnounce += printBoard();

   if (players[0] != nullptr)
      players[0]->send(toAnnounce);
   if (players[1] != nullptr)
      players[1]->send(toAnnounce);
}

// returns the string of name belonging to the session who's turn it is
string GameSession::getCurTurnName() const
{
   if (turn)
      return players[1]->getUserName();
   else
      return players[0]->getUserName();
}
