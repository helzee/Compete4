#include "board.h"
#include <iostream>
bool Board::dropPiece(int col, Owner player)
{
   for (int row = NUMROWS - 1; row >= 0; row--) {
      Slot &slot = board[row][col];
      if (!board[row][col].isOccupied()) {
         slot.setOwner(player);
         if (checkWin(player)) {
            cout << "WINNER" << endl;
         }
         return true;
      }
   }

   return false;
}

Board::Board() { reset(); }

bool Board::checkWin(Owner player)
{

   return checkWinHelper(player, 0, EAST, 0, 0);
}

void Board::determineRowCol(int &row, int &col, Direction dir)
{
   switch (dir) {
   case NORTH:
      row--;
      return;
   case NORTHEAST:
      col++;
      row--;
      return;
   case EAST:
      col++;
      return;
   case SOUTHEAST:
      col++;
      row++;
      return;
   case SOUTH:
      row++;
      return;
   case SOUTHWEST:
      row++;
      col--;
      return;
   case WEST:
      col--;
      return;
   case NORTHWEST:
      col--;
      row--;
      return;
   }
}

void Board::Slot::visit() { visited = true; }

bool Board::checkWinHelper(Owner player, int connected, Direction dir, int row,
                           int col)
{
   bool result;
   if (row < 0 || row > NUMROWS - 1 || col < 0 || col > NUMCOLS - 1) {
      return false;
   }
   int addition = 0;
   if (connected == FOUR) {
      return true;
   }
   Slot &slot = board[row][col];
   if (slot.isVisited()) {
      return false;
   }
   slot.visit();

   if (slot.isOccupied(player)) {
      addition = 1;
   }

   int counterA = 1; // c
   int counterB = 2;
   for (int i = 0; i < DIR_SIZE; i++) {
      int newRow = row;
      int newCol = col;
      determineRowCol(newRow, newCol, (Direction)i);

      if (i == dir) {

         result |=
             checkWinHelper(player, connected + addition, dir, newRow, newCol);
      } else {
         result |= checkWinHelper(player, addition, dir, newRow, newCol);
      }
   }
   return result;
}

bool Board::Slot::isOccupied(Owner player) const { return player == owner; }

bool Board::incrementTurn()
{
   turn++;
   if (turn >= NUMROWS * NUMCOLS) {
      isFull = true;
      return false;
   }
   return true;
}

void Board::reset()
{
   for (int i = 0; i < NUMROWS; i++) {
      for (int j = 0; j < NUMCOLS; j++) {
         board[i][j].reset();
      }
   }
   turn = 0;
   isFull = false;
}

string Board::print() const
{
   string connectBoard = "";
   // Print Board Top
   connectBoard += "|_._._._._._._|\n";
   // Board print per row
   // prints out 2x colnum characters
   for (int i = 0; i < NUMROWS; i++) {
      connectBoard += "|";
      for (int j = 0; j < (NUMCOLS * 2) - 1; j++) {
         // is a seperator char
         if (j % 2 == 0) {
            connectBoard += "T";
         }
         // is a token slot
         else {
            connectBoard += board[i][j - (j / 2)].print();
         }
      }
      connectBoard += "|\n";
   }
   // Print Board Base
   connectBoard += "/‾‾‾‾‾‾‾‾‾‾‾‾‾/\n";

   return connectBoard;
}

Board::Slot::Slot()
{
   owner = EMPTY;
   visited = false;
}

void Board::Slot::reset()
{
   owner = EMPTY;
   visited = false;
}

bool Board::Slot::isVisited() const { return visited; }
bool Board::Slot::isOccupied() const { return owner != EMPTY; }
void Board::Slot::setOwner(Owner player) { owner = player; }
string Board::Slot::print() const
{
   switch (owner) {
   case EMPTY:
      return SYMBOL_EMPTY;
   case P1:
      return SYMBOL_P1;
   case P2:
      return SYMBOL_P2;
   default:
      return "?";
   }
}

// bool Board::checkWin(Owner player)
//  {
//     int p1;
//     int p2;
//     // horizontal
//     for (int i = 0; i < NUMROWS; i++) {
//        p1 = 0;
//        p2 = 0;
//        for (int j = 0; j < NUMCOLS; j++) {
//           if (board[i][j] == 'o')
//        }
//     }
//     // vertical
//     for (int i = 0; i < NUMROWS; i++) {
//        for (int j = 0; j < NUMCOLS; j++) {
//           // check player1
//           if (board[i][j] == 'o' && board[i + 1][j] == 'o' &&
//               board[i + 2][j] == 'o' && board[i + 3][j] == 'o') {
//              return true;
//           }
//           // check player2
//           if (board[i][j] == 'x' && board[i + 1][j] == 'x' &&
//               board[i + 1][j] == 'x' && board[i + 1][j] == 'x') {
//              return true;
//           }
//        }
//     }
//     // descending diagonal
//     for (int i = 0; i < NUMROWS; i++) {
//        for (int j = 0; j < NUMCOLS; j++) {
//           // check player1
//           if (board[i][j] == 'o' && board[i - 1][j - 1] == 'o' &&
//               board[i - 2][j - 2] == 'o' && board[i - 3][j - 3] == 'o') {
//              return true;
//           }
//           // check player2
//           if (board[i][j] == 'x' && board[i - 1][j - 1] == 'x' &&
//               board[i - 2][j - 2] == 'x' && board[i - 3][j - 3] == 'x') {
//              return true;
//           }
//        }
//     }
//     // ascending diagonal
//     for (int i = 0; i < NUMROWS; i++) {
//        for (int j = 0; j < NUMCOLS; j++) {
//           // check player1
//           if (board[i][j] == 'o' && board[i - 1][j + 1] == 'o' &&
//               board[i - 2][j + 2] == 'o' && board[i - 3][j + 3] == 'o') {
//              return true;
//           }
//           // check player2
//           if (board[i][j] == 'x' && board[i - 1][j + 1] == 'x' &&
//               board[i - 2][j + 2] == 'x' && board[i - 3][j + 3] == 'x') {
//              return true;
//           }
//        }
//     }
//     return false;
//  }