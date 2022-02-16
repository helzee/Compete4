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
bool connectPlayer(Session* player) 
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
bool disconnectPlayer(Session* player) 
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
void resetBoard() {
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