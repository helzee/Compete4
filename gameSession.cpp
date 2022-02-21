#include "gameSession.h"


// ----------------------------------------------------------------------------
//  Public Methods
// ----------------------------------------------------------------------------

// Constructor
GameSession::GameSession(int id)
{
    // Sets the fed gameid from gameDB into this game's identifier
    gameID = id;
    // Initialize the board with empty spaces
    // Set the number of tokens in each column to 0
    // Player one will use: x
    // Player two will use: o
    for(int i = 0; i < BOARD_ROW; i++) 
    {
        for(int j = 0; j < BOARD_COL; j++) 
        {
            board[i][j] = ' ';
            // # of tokens in each col
            colCount[j] = 0;
        }
    }

    // Setting the players to empty
    players[0] = nullptr;
    players[1] = nullptr; 

    //Other fields set in header
}

// Connect Player
bool GameSession::connectPlayer(Session* player) 
{
    // if ingame, two players already connected
    if (inGame) 
    {
        send("Error Connecting: Game Full", player->sd);
        return false;
    } 
    // Check player one slot
    if (players[0] != nullptr) 
    {
        players[0] == player;
        player.currGame = this;
    }
    // Check player two slot, if empty, add and set ingame to true
    else if (players[1] != nullptr) 
    {
        players[1] == player; 
        player.currGame = this;
        inGame = true;
        // upon game-start, reset the game state
        resetBoard();
    }
    // Just in case, inGame boolean problem and full game
    send("Error Connecting: Game Full", player->sd);
    return false; 
}

// Disconnect Player
// *change player currmenu in commandParser
bool GameSession::disconnectPlayer(Session* player) 
{
    // doesn't matter if ingame
    // check player one
    if(players[0]->getSessionID() == player->getSessionID()) 
    {
        // disconnect players and player's current game
        player.currGame == nullptr;
        players[0] == nullptr;
        send("Successfully disconnected from game", player->sd);
        return true;
    }
    // check player two
    else if(players[1]->getSessionID() == player->getSessionID()) 
    {
        // disconnect players and player's current game
        player.currGame == nullptr;
        players[1] == nullptr;
        send("Successfully disconnected from game", player->sd);
        return true;
    }
    send("Error Disconnecting: Not player not in target game", player->sd);
    return false;
}

// Resets board when both players have connected to the game
// Check connnectPlayer
void GameSession::resetBoard() {
    // Set the number of tokens in each column to 0
    // Player one will use: x
    // Player two will use: o
    for(int i = 0; i < BOARD_ROW; i++) 
    {
        for(int j = 0; j < BOARD_COL; j++) 
        {
            board[i][j] = ' ';
            // # of tokens in each col
            colCount[j] = 0;
        }
    }
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
String GameSession::printBoard() {
    string connectBoard = "";
    // Print Board Top
    connectBoard += "|_._._._._._._|\n";
    // Board print per row
    // prints out 2x colnum characters
    for(int i = 0; i < BOARD_ROW; i++) 
    {
        connectBoard += "|";
        for(int j = 0; j < (BOARD_COL*2)-1; j++)
        {
            // is a seperator char
            if ( i % 2 == 0) {
                connectBoard += "T";
            }
            // is a token slot
            else
            {
                connectBoard += board[i][j - (j/2)];
            }
        }
        connectBoard += "|\n";
    }
    // Print Board Base
    connectBoard += "/‾‾‾‾‾‾‾‾‾‾‾‾‾/\n"
    return connectBoard;
}


// ----------------------------------------------------------------------------
//  Private Methods
// ----------------------------------------------------------------------------

// Part of game
// Determines if session attempting to change the gamestate is an active player within the game
bool partOfGame(Session* sender) 
{
    // Check players one and two
    if (players[0]->getSessionID() == sender->getSessionID())
        return true;
    else if (players[1]->getSessionID() == sender->getSessionID())
        return true;
    return false;
}

// Determines if the player sending information is allowed to move
// Helper used in droppiece
bool isTurn(Session* player)
{
    // Determine if player is p1 or p2 slot
    // Compare with turn boolean: false = p1, true = p2
    if (players[0]->getSessionID() == sender->getSessionID())
    {
        if(isTurn == false)
            return true; 
    }
    else if (players[1]->getSessionID() == sender->getSessionID())
    {
        return true;    
    }
}

// Checks for the win condition
// Used after every droppiece so if connect four is achieved, the game is over
bool checkWin() {
    // horizontal
    for (int i = 0; i < BOARD_ROW; i++) 
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            // check player1
            if (board[i][j] == 'o' &&
                board[i][j+1] == 'o' &&
                board[i][j+2] == 'o' &&
                board[i][j+3] == 'o' &&)
            {
                return true;
            }
            // check player2
            if (board[i][j] == 'x' &&
                board[i][j+1] == 'x' &&
                board[i][j+2] == 'x' &&
                board[i][j+3] == 'x' &&)
            {
                return true;
            }
        }
    }
    // vertical
    for (int i = 0; i < BOARD_ROW; i++) 
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            // check player1
            if (board[i][j] == 'o' &&
                board[i+1][j] == 'o' &&
                board[i+2][j] == 'o' &&
                board[i+3][j] == 'o' &&)
            {
                return true;
            }
            // check player2
            if (board[i][j] == 'x' &&
                board[i+1][j] == 'x' &&
                board[i+1][j] == 'x' &&
                board[i+1][j] == 'x' &&)
            {
                return true;
            }
        }
    }
    // descending diagonal
    for (int i = 0; i < BOARD_ROW; i++) 
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            // check player1
            if (board[i][j] == 'o' &&
                board[i-1][j-1] == 'o' &&
                board[i-2][j-2] == 'o' &&
                board[i-3][j-3] == 'o' &&)
            {
                return true;
            }
            // check player2
            if (board[i][j] == 'x' &&
                board[i-1][j-1] == 'x' &&
                board[i-2][j-2] == 'x' &&
                board[i-3][j-3] == 'x' &&)
            {
                return true;
            }
        }
    }
    // ascending diagonal
    for (int i = 0; i < BOARD_ROW; i++) 
    {
        for (int j = 0; j < BOARD_COL; j++)
        {
            // check player1
            if (board[i][j] == 'o' &&
                board[i-1][j+1] == 'o' &&
                board[i-2][j+2] == 'o' &&
                board[i-3][j+3] == 'o' &&)
            {
                return true;
            }
            // check player2
            if (board[i][j] == 'x' &&
                board[i-1][j+1] == 'x' &&
                board[i-2][j+2] == 'x' &&
                board[i-3][j+3] == 'x' &&)
            {
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