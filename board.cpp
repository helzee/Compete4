#include "board.h"
/**
 * @brief If valid move, drop token into slot, increment turn counter,
 * and check for win
 * @pre game should be in progress (not finished). col should be between
 * 0 and NUMCOLS (inclusive)
 * @post after this function call, a valid move can lead to the game to end
 * either through turn count reaching it's max or by a player winning. board
 * condition (isFinished) SHOULD be checked after each call of dropPiece()
 *
 * @param col the slot to drop the token into (0->NUMCOLS is left->right)
 * @param player the player dropping the token
 * @return true if valid move
 * @return false if invalid move
 */
bool Board::dropPiece(int col, Owner player)
{
   if (col < 0 || col > NUMCOLS - 1 || isFinished) {
      return false;
   }
   for (int row = NUMROWS - 1; row >= 0; row--) {
      Slot &slot = board[row][col];
      if (!board[row][col].isOccupied()) {
         slot.setOwner(player);
         incrementTurn();
         if (checkWin(player, row, col)) {

            winner = player;
            isFinished = true;
         }
         return true;
      }
   }

   return false;
}

/***/
Board::Board() { reset(); }

bool Board::checkWin(Owner player, int row, int col) const
{
   // northsound, only have to check south, cuz nothing above new token
   int NorthSouth = checkWinHelper(player, 0, SOUTH, row, col);
   int EastWest = checkWinHelper(player, 0, EAST, row, col) +
                  checkWinHelper(player, -1, WEST, row, col);
   int NESW = checkWinHelper(player, 0, NORTHEAST, row, col) +
              checkWinHelper(player, -1, SOUTHWEST, row, col);
   int NWSE = checkWinHelper(player, 0, NORTHWEST, row, col) +
              checkWinHelper(player, -1, SOUTHEAST, row, col);
   // middle tokend is counted in both helpers, so subtract 1
   return NWSE >= FOUR || NESW >= FOUR || EastWest >= FOUR ||
          NorthSouth >= FOUR;
}

void Board::determineRowCol(int &row, int &col, Direction dir) const
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

int Board::checkWinHelper(Owner player, int connected, Direction dir, int row,
                          int col) const
{
   // if out of bounds
   if (row < 0 || row > NUMROWS - 1 || col < 0 || col > NUMROWS - 1) {
      return connected;
   }

   const Slot &slot = board[row][col];

   // if player has token in this slot
   if (slot.isOccupied(player)) {
      connected++;
   } else { // if not, dont check this direction anymore
      return connected;
   }

   // if connect4!
   if (connected >= FOUR) {
      return connected;
   }
   int newRow = row, newCol = col;
   determineRowCol(newRow, newCol, dir);
   // check win in this direction and opposite direction
   connected = checkWinHelper(player, connected, dir, newRow, newCol);

   return connected;
}

bool Board::incrementTurn()
{
   turnCount++;
   if (turnCount >= NUMROWS * NUMCOLS) {
      isFinished = true;
      return false;
   }
   return true;
}

Owner Board::getWinner() const { return winner; }
bool Board::haveWinner() const { return winner != EMPTY; }

void Board::reset()
{
   for (int i = 0; i < NUMROWS; i++) {
      for (int j = 0; j < NUMCOLS; j++) {
         board[i][j].reset();
      }
   }
   turnCount = 0;
   isFinished = false;
   winner = EMPTY;
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

Board::Slot::Slot() { owner = EMPTY; }

void Board::Slot::reset() { owner = EMPTY; }

bool Board::Slot::isOccupied() const { return owner != EMPTY; }
bool Board::Slot::isOccupied(Owner player) const { return player == owner; }
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
