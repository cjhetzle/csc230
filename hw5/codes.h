/**
  @file codes.h
  @author Cameron Hetzler cjhetzle

*/

#ifndef _CODES_H_
#define _CODES_H_

/**
  Given the ASCII code for a character, this function returns the 5bit
   code used to represent it. For example, if you call symToCode( 'a' ),
   it should return 2.

   @param the system we create the code for
   @return the int code we want to return for the given symbol
*/
int symToCode( unsigned char ch );

/**
  Given a 5bit code, this function returns the ASCII character it represents.
   For example, if you call codeToSym( 2 ), it should return the ASCII code for a.

   @param the code you want to find the symbol to
   @return the ASCII code for the symbol you want
*/
int codeToSym( int code );

#endif