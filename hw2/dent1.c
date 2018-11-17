#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void indent ( int d ) {
  for ( int i = 0; i < d; i++ ) {
    putchar(' ');
  }
}

_Bool isASpace( char ch ) {
  if ( ch == 32 || ch == 9 ) {
    return true;
  } else {
    return false;
  }
}

char discardSpaces() {
  char ch;
  do {
    ch = getchar();
  } while (isASpace(ch));

  return ch;
}

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

    if (ch == '\n') {
      ch = discardSpaces();
      if (ch == '}') {
        a_indent -= 2;
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