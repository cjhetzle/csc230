/**
  @file dent.c
  @author cameron hetzler

  The program will indent a file based on the brackets
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


/**
  prints out the number of spaces denoted by d

  @param d how many spaces to print
*/
void indent ( int d ) {
  for ( int i = 0; i < d; i++ ) {
    putchar(' ');
  }
}


/**
  Checks to see if the char given is a space or a tab

  @param ch the char in question
  @return true if the char is a space or tab
*/
_Bool isASpace( char ch ) {
  if ( ch == 32 || ch == 9 ) {
    return true;
  } else {
    return false;
  }
}


/**
  This method discards all the spaces and 
  tabs that appear at the start of a line
*/
char discardSpaces() {
  char ch;
  do {
    ch = getchar();
  } while (isASpace(ch));

  return ch;
}

/**
  This program will output a file with the correct indenttation
*/
int main() {
  char ch = discardSpaces();
  int a_indent = 0;
  do
  {
    if (ch == '}') {
      a_indent -= 2;
    } else if (ch == '{') {
      a_indent += 2;
    }
    
    putchar(ch);

    //Most of the work is done at the end of a line when the char is \n
    if (ch == '\n') {
      ch = discardSpaces();
      if (ch == '}') {
        a_indent -= 2;
        if (a_indent < 0) {
          printf("Unmatched brackets\n");
          exit(100);
        }
      }

      if (ch == EOF && a_indent != 0) {
        printf("Unmatched brackets\n");
        return 100;
      } else if (ch != '\n') {

        indent(a_indent);

        if (ch == '{') {
          a_indent += 2;
        }

        if (ch != EOF) {
          putchar(ch);
        } else {
          if (a_indent != 0) {
            printf("Unmatched brackets\n");
            return 100;
          }
          return 0;
        }

      } else {
        putchar(ch);
        indent(a_indent);
      }
    }
  } while ((ch = getchar()) != EOF);

  if (a_indent != 0) {
    printf("Unmatched brackets\n");
    return 100;
  }  

  return 0;
}
