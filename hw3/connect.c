/**
  @file connect.c
  @author Cameron Hetzler

  Play connect 4
  */

#include "board.h"
#include <stdio.h>
#include <stdlib.h>

/** links game status between board.c and connect.c */
int status;

/**
  A game of connect 4 with a friend
  */
int main() {
  int rows, cols;
  printf("Rows and cols> ");
  if (0 == scanf("%d %d", &rows, &cols) ||
       rows < 4 || rows > 20 ||
       cols < 4 || cols > 20) {
    fprintf(stderr, "Invalid board size\n");
    exit(1);
  }
  char board[rows][cols];
  char player = 'X';
  status = 0;
  clearBoard( rows, cols, board );

  while ( !status ) {
    printBoard( rows, cols, board );

    makeMove( player, rows, cols, board );

    gameStatus( rows, cols, board );

    if ( status != 0 ) {
      break;
    }

    player = ( player == 'X' ) ? 'O': 'X';
  }

  printBoard( rows, cols, board );

  if ( status == 1 ) {
    printf("Player %c wins\n", player);
  } else {
    printf("Stalemate\n");
  }
  return 0;
}