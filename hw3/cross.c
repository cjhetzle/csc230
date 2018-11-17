#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define W_LENGTH 20
#define W_COUNT 100000

//global variables
static char words[W_COUNT][W_LENGTH];
int wordCount;

//prototypes
void readWords( char const *filename );
bool getPattern( char *pat );
bool matches( char const *word, char const *pat );

int main( int argc, char *argv[] ) {

  char pattern[W_LENGTH] = {};

  //get name of file
  if ( argc != 2 ) {
    fprintf( stderr, "usage: cross <word-file>\n" );
    exit(1);
  }

  readWords( argv[1] );

  while (true) {

    for (int i = 0; i < W_LENGTH; i++) {
      pattern[i] = 0;
    }

    while ( !getPattern( pattern ) ) {
      printf("Invalid pattern\n");
      for (int i = 0; i < W_LENGTH; i++) {
        pattern[i] = 0;
      }
    }

    for (int i = 0; i < wordCount; i++ ) {
      if ( matches( words[i], pattern ) ) {
        for (int j = 0; words[i][j] != 0; j++) {
          putchar(words[i][j]);
        }
        putchar('\n');
      }
    }
  }

  exit(0);
}

void readWords( char const *filename ) {
  //Read the word list from the file with the given name, storing it
  //in the global words array and setting wordCount.
  //this function takes a pointer to a list of char

  FILE *fp = fopen( filename, "r" );

  if (fp == NULL) {
    fprintf(stderr, "Can't open word file\n");
    exit(1);
  }

  char val[W_LENGTH];
  while ( fscanf( fp, "%s", val ) == 1 ) {
    if ( (int)strlen(val) > W_LENGTH || wordCount == W_COUNT ) {
      fprintf(stderr, "Invalid word file\n");
      exit(1);
    }
    for ( int i = 0; i < (int)strlen(val); i++ ) {

      if ( val[i] < 'a' || val[i] > 'z' ) {
        fprintf(stderr, "Invalid word file\n");
        exit(1);
      }
      words[wordCount][i] = val[i];
    }
    wordCount++;

    for (int i = 0; i < W_LENGTH; i++) {
      val[i] = 0;
    }

  }

  fclose( fp );
}

bool getPattern( char *pat ) {
  //this prompts the users for a pattern and stores it in the given
  //array pat. return true when user inputs a valid pattern, or false
  //if the function reaches EOF before a valid pattern is found.

  bool exit_status = true;
  //prompt the use for input
  printf("pattern> ");

  char c = 0; int i = 0;
  while ( (c = getchar()) != '\n' ) {
    if ( c == 63 || (c >= 'a' && c <= 'z') ) {
      pat[i] = c;
      i++;
    } else if ( c == EOF) {
      exit(0);
    } else {
      exit_status = false;
    }
  }

  if ( i > W_LENGTH )
    exit_status = false;

  return exit_status;
}

bool matches( char const *word, char const *pat ) {
  //given a word and a pattern the function will return true if the
  //word matches the pattern.

  bool exit_status = true;

  for ( int i = 0; i < W_LENGTH; i++ ) {
    if ( pat[i] == 63 ) {
      if ( word[i] == 0 ) {
        exit_status = false;
        break;
      }
      continue;
    } else if ( pat[i] != word[i] ) {
      return false;
    }
  }

  return exit_status;
}
