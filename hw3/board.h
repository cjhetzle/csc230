#include <stdbool.h>

// This trick will let us define the length of a winning
// run when we compile the program, if we want to.
#ifndef RUNLEN
/** Number of markers in a row required for a win. */
#define RUNLEN 4
#endif

/**
   Return true if there's a winning sequence of markers starting at
   the given board location, startRow, startCol location, either a
   sequence of X characters or O characters.  The dRow and dCol
   parameters indicate what direction to look, with dRow giving
   change-in-row for each step and dCol giving the change-in-column.
   For example, a dRow of -1 and a dCol of 1 would looK for a sequence
   of markers starting from the given start location and diagonally up
   to the right.
   @param rows Number of rows the board has.
   @param cols Number of columns the board has.
   @param board The game board.
   @param startRow Row start position to look for a win.
   @param startCol Column start position to look for a win.
   @param dRow Direction to move vertically looking for a win.
   @param dCol Direction to move horizontally looking for a win.
   @return true if there's a win in the given board location.
 */
bool winner( int rows, int cols, char board[ rows ][ cols ],
             int startRow, int startCol, int dRow, int dCol );

/**
  this will print the current board for the player to see

  @param rows Rows in the board
  @param cols Colc in the board
  @board the 2D array of chars that represent the board
  */
void printBoard( int rows, int cols, char board[ rows ][ cols ] );

/**
  Resets all moves on the board to spaces

  @param player the player char to user
  @param rows rows of the board
  @param cols columns of the board
  @param board A representation of the board
  */
void clearBoard( int rows, int cols, char board[ rows ][ cols ] );

/**
  Checks to see if there was a set of 4 moves ina row

  @param rows Number of rows in the board
  @param cols Number of columns in the board
  @param board 2d array of player moves
  */
void gameStatus( int rows, int cols, char board[ rows ][ cols ] );

/**
  This function prompts the user for their next move.
  The given player char indicates which palyer has the next move

  @param player the player char to user
  @param rows rows of the board
  @param cols columns of the board
  @param board A representation of the board
  */
void makeMove( char player, int rows, int cols, char board[ rows ][ cols ] );

/** links game status between board.c and connect.c */
int extern status;
