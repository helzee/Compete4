/** @file gameSession.h
 * 
 */
#include "constants.h"
#include "session.h"

#ifndef GAMESESSION_H
#define GAMESESSION_H

using namespace std;

class gameSession
{
public:
    int gameID;
    
    bool connectPlayer(Session*);
    bool disconnectPlayer(Session*);
    void resetBoard(Session*);

    bool dropPiece(Session*, int);
    string printBoard(Session*);

    gameSession(int);

private:
    Session* players[2];
    char board[BOARD_ROW][BOARD_COL];
    int colCount[BOARD_COL];
    bool turn = false;
    bool inGame = false;
    
    bool partOfGame(Session*);
    bool isTurn(Session*);
    bool checkWin();
    void announceUpdate();
};

#endif