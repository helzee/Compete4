#include "gameSession.h"

using namespace std;

int gameCounter = 0;

void makeGame() {
    if(gameCounter < MAX_GAMES)
        gameSession* newGame = new gameSession(gameCounter++);
        gameList[gameCounter] = newGame;
    }
}

gameSession* getGame(int) {
    if(int <= MAX_GAMES)
        return gameList[int];
    return nullptr;
}