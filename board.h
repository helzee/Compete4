
#ifndef BOARD_H
#define BOARD_H

#include <string>

using namespace std;

#define NUMROWS 6
#define NUMCOLS 7

#define SYMBOL_EMPTY " "
#define SYMBOL_P1 "o"
#define SYMBOL_P2 "x"
#define FOUR 4

// NONE, P1, P2
const char slotSymbols[]{' ', 'o', 'x'};

enum Symbol { NONE, P1, P2 };

// player 1, 2, or neither
enum Owner { EMPTY, P1, P2 };

enum Direction {
   NORTH,
   NORTHEAST,
   EAST,
   SOUTHEAST,
   SOUTH,
   SOUTHWEST,
   WEST,
   NORTHWEST,
   DIR_SIZE
};

class Board
{
public:
   Board();
   bool dropPiece(int, Owner);
   string print() const;

   Owner getWinner() const;
   bool haveWinner() const;
   void reset();

private:
   bool incrementTurn();
   bool checkWin(Owner, int, int) const;
   int checkWinHelper(Owner player, int connected, Direction dir, int row,
                      int col) const;
   void determineRowCol(int &, int &, Direction) const;
   class Slot
   {
   public:
      Slot();
      void reset();
      bool isVisited() const;
      bool isOccupied() const;
      bool isOccupied(Owner) const;
      void setOwner(Owner);
      char print() const;

   private:
      // owner of this slot
      Owner owner;
      Symbol symbol;
   };
   Slot board[NUMROWS][NUMCOLS];
   bool isFinished;
   Owner winner;
   int turnCount;
};

#endif