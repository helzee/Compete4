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

#include <iostream>

// TIE HOTFIX: returns int, -1 for failure, 0 for successful drop,

bool Board::dropPiece(int col, Owner player)
{
   if (col < 0 || col > NUMCOLS - 1 || isFinished) {
      return false;
   }
   for (int row = NUMROWS - 1; row >= 0; row--) {
      Slot &slot = board[row][col];
      if (!board[row][col].isOccupied()) {
         slot.setOwner(player);
         std::cerr << "Set slot " << row << " " << col << std::endl;
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

bool Board::getIsFinished() const { return isFinished; }

/**
 * @brief Construct a new Board:: Board object. Initialize it.
 *
 */
Board::Board() { reset(); }

/**
 * @brief checks to see if the given player has won the game. this function
 * should be called inside of dropPiece() after any piece is dropped. It starts
 * at the newly dropped piece, and checks in every direction (except north,
 * since no pieces could be above a newly dropped piece) to see if 4 tokens of
 * this player have been connected
 *
 * @param player the player whose tokens we are counting
 * @param row the current row we are in
 * @param col the current collumn we are in
 * @return true : this player has won
 * @return false : this player has not won
 */
bool Board::checkWin(Owner player, int row, int col) const
{
   // northsound, only have to check south, cuz nothing above new token
   // add up total east and west tokens. subtract 1 from one of the helper
   // functions so that we dont count the starting token twice
   int NorthSouth = checkWinHelper(player, 0, SOUTH, row, col);
   int EastWest = checkWinHelper(player, 0, EAST, row, col) +
                  checkWinHelper(player, -1, WEST, row, col);
   int NESW = checkWinHelper(player, 0, NORTHEAST, row, col) +
              checkWinHelper(player, -1, SOUTHWEST, row, col);
   int NWSE = checkWinHelper(player, 0, NORTHWEST, row, col) +
              checkWinHelper(player, -1, SOUTHEAST, row, col);
   return NWSE >= FOUR || NESW >= FOUR || EastWest >= FOUR ||
          NorthSouth >= FOUR;
}

/**
 * @brief Determine the next slot to finished (based on the direction we are
 * heading)
 *
 * @param row current row we are at
 * @param col current collumn we are at
 * @param dir the direction we want to go
 */
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

/**
 * @brief Recursive helper function that checks slots. it moves in the direction
 * given in the parameters. It stops if it goes out of the board, finds a slot
 * not occupied by the player, or finds 4 consecutive player tokens. It returns
 * the total number of this players tokens in came across on its journey
 *
 * @param player the player whose tokens we are counting
 * @param connected how many tokens we have found so far
 * @param dir direction we are heading
 * @param row the current row we are in
 * @param col the current collumn we are in
 * @return int : total connected tokens found in this journey
 */
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

/**
 * @brief increments the total turn counter. checks if the game is finished. if
 * it is, change the state of the game: set isfinished to true
 * @pre game should not be finished and a successful move should have been
 * completed
 * @post turnCount is incremented and isFinished is possibly set to true
 *
 * @return true if game is not finished
 * @return false if game is finished
 */
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

// do we have a winner?
bool Board::haveWinner() const { return winner != EMPTY; }

/**
 * @brief Reset the board and game logic
 *
 */
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
string Board::print() const
{
   string connectBoard = "";
   // Print Board Top
   connectBoard += "|1|2|3|4|5|6|7|\n";
   connectBoard += "|_._._._._._._|\n";
   // Board print per row
   // prints out 2x colnum characters
   for (int i = 0; i < NUMROWS; i++) {
      connectBoard += "|";
      for (int j = 0; j < (NUMCOLS * 2) - 1; j++) {
         // is a seperator char
         if (j % 2 == 1) {
            connectBoard += ":";
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
   symbol = SYMEMPTY;
}

void Board::Slot::reset() { owner = EMPTY; }

bool Board::Slot::isOccupied() const { return owner != EMPTY; }
bool Board::Slot::isOccupied(Owner player) const { return player == owner; }
void Board::Slot::setOwner(Owner player)
{
   owner = player;
   symbol = (Symbol)owner;
}

/**
 * @brief Prints this slot's symbol as a character (defined in slotSymbols array
 * in the header)
 *
 * @return char symbol
 */
char Board::Slot::print() const { return slotSymbols[symbol]; }
