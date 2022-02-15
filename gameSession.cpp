#include "gameSession.h"

// ----------------------------------------------------------------------------
//  Public Methods
// ----------------------------------------------------------------------------

// Constructor
gameSession::gameSession()
{
    // Initialize the board with empty spaces
    // Set the number of tokens in each column to 0
    // Player one will use: x
    // Player two will use: o
    for(int i = 0; i < BOARD_ROW; i++) {
        for(int j = 0; j < BOARD_COL; j++) {
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
bool connectPlayer(Session* player) {
    // if ingame, two players already connected
    if (inGame)
        return false;
    // Check player one slot
    if (players[0] != nullptr) 
        players[0] == player;
    // Check player two slot, if empty, add and set ingame to true
    if (players[1] != nullptr)
        players[1] == player; inGame = true;
    // Just in case, inGame boolean problem and full game
    return false;     
}

// Disconnect Player
bool disconnectPlayer(Session* player) {
    return true;
}

// ----------------------------------------------------------------------------
//  Private Methods
// ----------------------------------------------------------------------------

