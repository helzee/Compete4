
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
   bool checkWin(Owner);
   void reset();
   bool incrementTurn();

private:
   bool checkWinHelper(Owner player, int connected, Direction dir, int row,
                       int col);
   void determineRowCol(int&, int&, Direction);
   class Slot
   {
   public:
      Slot();
      void reset();
      bool isVisited() const;
      bool isOccupied() const;
      bool isOccupied(Owner) const;
      void setOwner(Owner);
      string print() const;
      void visit();

   private:
      // owner of this slot
      Owner owner;
      // used in check win algo
      bool visited;
   };
   Slot board[NUMROWS][NUMCOLS];
   int turn;
   bool isFull;
   bool hasWon;
};

#endif