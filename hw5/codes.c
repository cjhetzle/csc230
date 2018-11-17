/**
  @file codes.c
  @author Cameron Hetzler cjhetzle

  This will contian functions to help map between symbols and the codes used to represent them.
  This component will be easy to write,
  but you may want to think about how to make it efficient, to handle large files quickly
*/

#include "codes.h"

char syms[31] = { 
  'e', 't', 'a', 'i', '"', 'n', ' ', 's', 'o', 'l', 'r',
  'd', 'c', '>', '<', '/', 'p', 'm', '-', 'u', '.', 'h',
  'f', '_', '=', 'g', ':', 'b', '0', 'y', '\n' };

int symToCode( unsigned char ch ) {
  for ( int i = 0; i < 31; i++ ) 
    if ( syms[i] == ch )
      return i;
  
  return 31;
}

int codeToSym( int code ) {
  return syms[code];
}
