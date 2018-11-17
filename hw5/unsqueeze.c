/**
  @file unsqueeze.c
  @author Cameron Hetzler cjhetzle
  
  this funciton is responsible to obtaining the readable version of a file
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
    return ErrorMessage("usage: unsqueeze <infile> <outfile>");

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
  int code = read5Bits( &buffer, rfp );
  if ( code != 1 )
    return ErrorMessage("Invalid compressed format");
  /** initialize two ints, ch will read characters and is an int
    so EOF will appear as -1. */
  int ch;
  /** Iterate through the file until EOF is hit */
  while ( (code = read5Bits( &buffer, rfp ) ) != -1 ) {
    if ( code == 31 ) {
      if ( (code = read8Bits( &buffer, rfp ) ) == -1)
        break;
      ch  = code;
    } else {
      //find the code for the character
      ch = codeToSym( code );
    }
    //write the 5-bit code to the file/buffer
    fputc( ch, wfp );
    //if the code is 31 also write the full length char
    
  }
  /** the program was succesful, empty the ramains of the buffer
    and exit with a status of 0 */
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