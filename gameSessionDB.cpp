#include "gameSession.h"

using namespace std;

// Counter for number of games, also used for session ID
int gameCounter = 0;

// Create a new gamesession
// Add to the database/list
void makeGame() {
    if(gameCounter < MAX_GAMES)
        gameSession* newGame = new gameSession(gameCounter++);
        gameList[gameCounter] = newGame;
    }
}

// Hands off the gameSession object pointer to player's session
gameSession* getGame(int) {
    if(int <= MAX_GAMES)
        return gameList[int];
    return nullptr;
}