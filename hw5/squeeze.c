/**
  @file squeeze
  @author Cameron Hetzler cjhetzle
  
  This program will take a test file and create a new binary file that is
  smaller in size and unreadable by anyone else.
  idea is to take an 8-bit char that only uses the first 5-bits and just
  print those.
*/

#include <stdlib.h>
#include <string.h>
#include "bits.h"
#include "codes.h"

/**
  Used to stream line error reporting into one line

  @param the message that you want to send to stderr
  @return the exit status reported
*/
int ErrorMessage( char *msg );

int main( int argc, char *argv[] ) {
  /** Check to see if the correct number of arguments were passed */
  if ( argc != 3 )
    return ErrorMessage("usage: squeeze <infile> <outfile>");

  /** create strings for the names of the file/directories */
  char *inFile = argv[1], *outFile = argv[2];
  /** declare the variables for the files to read and write */
  FILE *rfp = fopen( inFile, "rb" ),
    *wfp = fopen( outFile, "wb" );
  /** check to see if the files were accessed succesfully,
    if not exit with status 1 after writing error to stderr */
  if ( rfp == NULL )
    return ErrorMessage( strcat(inFile, ": No such file or directory") );
  else if ( wfp == NULL )
    return ErrorMessage( strcat(outFile, ": No such file or directory") );
  /** initialize the buffer to zero */
  BitBuffer buffer = { 0, 0 };
  /** write the initial 5 bits for the compression code */
  write5Bits( 1, &buffer, wfp );
  /** initialize two ints, ch will read characters and is an int
    so EOF will appear as -1. */
  int ch, code;
  /** Iterate through the file until EOF is hit */
  while ( (ch = fgetc( rfp )) != -1 ) {
    //find the code for the character
    code = symToCode( ch );
    //write the 5-bit code to the file/buffer
    write5Bits( code, &buffer, wfp );
    //if the code is 31 also write the full length char
    if ( code == 31 ) 
      write8Bits( ch, &buffer, wfp );
  }
  /** the program was succesful, empty the ramains of the buffer
    and exit with a status of 0 */
  flushBits( &buffer, wfp );

  fclose( wfp );
  fclose( rfp );

  exit(0);
}

int ErrorMessage( char *msg ) {
  /** print the message passed to the stderr
    add a new line to the end and exit with
    a status of 1 */
  fprintf(stderr, "%s\n", msg );
  return 1;
}