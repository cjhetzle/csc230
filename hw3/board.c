/**
  @file board.c
  @author Cameron Hetzler

  A connect four game
  */
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool winner( int rows, int cols, char board[ rows ][ cols ],
 int startRow, int startCol, int dRow, int dCol ) {
  // Number of X and O symbols in this sequence of locations
  int xcount = 0, ocount = 0;

  // Walk down the sequence of board spaces.
  for ( int k = 0; k < RUNLEN; k++ ) {

    // Figure out its row and column index and make sure it's on the board.
    int r = startRow + k * dRow;
    int c = startCol + k * dCol;
    if ( r < 0 || r >= rows || c < 0 || c >= cols )
      return false;

    // Count an X or an O if it's one of those.
    if ( board[ r ][ c ] == 'X' )
      xcount++;
    else if ( board[ r ][ c ] == 'O' )
      ocount++;
  }

  // We have a winner if it's all Xs or Os.
  return xcount == RUNLEN || ocount == RUNLEN;
}

void printBoard( int rows, int cols, char board[ rows ][ cols ] ) {
  //start with a fresh line
  putchar('\n');

  for (int y = 0; y < rows; y++) {
    putchar('|');
    for (int x = 0; x < cols; x++) {
      putchar(board[y][x]);
      putchar('|');

    }
    putchar('\n');
  }

  putchar('+');
  for (int x = 0; x < cols; x++) {
    putchar('-');
    putchar('+');
  }
  putchar('\n');
  for (int x = 0; x < cols; x++) {
    printf(" %1d", (x + 1) % 10);
  }
  putchar('\n');
}

void clearBoard( int rows, int cols, char board[ rows ][ cols ] ) {
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      board[y][x] = ' ';
    }
  }
}

void gameStatus( int rows, int cols, char board[ rows ][ cols ] ) {
  for ( int y = 0; y < rows; y++ ) {
    for (int x = 0; x < cols; x++ ) {
      if ( board[ y ][ x ] != ' ' ) {
        //check up
        if (winner( rows, cols, board, y, x, -1, 0 ) == 1 || 
          winner( rows, cols, board, y, x, 1, 0 ) == 1 ||
          winner( rows, cols, board, y, x, 0, -1 ) == 1 ||
          winner( rows, cols, board, y, x, 0, 1 ) == 1 ||
          winner( rows, cols, board, y, x, 1, 1 ) == 1 ||
          winner( rows, cols, board, y, x, 1, -1 ) == 1 ||
          winner( rows, cols, board, y, x, -1, -1 ) == 1 ||
          winner( rows, cols, board, y, x, -1, 1 ) == 1) {
          status = 1;
        }
      }
    }
  }
}

void makeMove( char player, int rows, int cols, char board[ rows ][ cols ] ) {
  printf("%c move> ", player);
  int move = 0;
  int error = 0;

  error = scanf("%d", &move);  

  move--;

  if (error == 0 || move < 0 || move > cols - 1 || board[ 0 ][ move ] != ' ') {
    char ch;
    while ( (ch = getchar()) != '\n' && ch != EOF) {
      //nothing
    }
    if ( ch == '\n' ) {
      printf("Invalid move\n");
      makeMove( player, rows, cols, board );
      return;
    } else {
      exit(0);
    }
    makeMove( player, rows, cols, board );
    return;
  }

  for ( int i = rows - 1; i >= 0; i-- ) {
    if ( board[ i ][ move ] == ' ' ) {
      board[ i ][ move ] = player;
      if ( i == 0 ) {
        status = 2;
        for ( int j = 0; j < cols; j++ ) {
          if (board[ 0 ][ j ] == ' ') {
            status = 0;
          }
        }
      }
      return;
    }
  }
}