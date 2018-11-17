/**
  @file bits.c
  @author Cameron Hetzler cjhetzle

  This will define functions for writing out bit sequences to and from a file.
  With the help of these functions,
  it will be easy for the main program to read and write the 5-bit and 8-bt
  codes needed for compression.
*/

#include "bits.h"

/**
  This is just a handy method to easily shift
  a variable over some number

  @param a pointer to an unsigned char to shift
  @param an integer value of the amount to shift by
*/
void shiftVal( unsigned char *val, int shift );

void write5Bits( int code, BitBuffer *buffer, FILE *fp ) {
  int shift = 3 - buffer->bcount;
  unsigned char new_byte = shift >= 0 ? code << shift: code >> (shift * -1);

  buffer->bits = buffer->bits | new_byte;

  buffer->bcount += shift >= 0 ? 5: 5 + shift;

  if ( buffer->bcount >= BITS_PER_BYTE ) {
    fputc( buffer->bits, fp );
    buffer->bits = 0;
    buffer->bcount = 0;

    if ( shift < 0 ) {
      shift = BITS_PER_BYTE + shift;
      new_byte = shift >= 0 ? code << shift: code >> (shift * -1);

      buffer->bits = buffer->bits | new_byte;

      buffer->bcount += (BITS_PER_BYTE) - shift;
    }
  }
}

void write8Bits( int code, BitBuffer *buffer, FILE *fp ) {
  int shift = -1 * buffer->bcount;
  unsigned char new_byte = shift >= 0 ? code << shift: code >> (shift * -1);

  buffer->bits = buffer->bits | new_byte;

  buffer->bcount += shift >= 0 ? 8: 8 + shift;

  if ( buffer->bcount >= BITS_PER_BYTE ) {
    fputc( buffer->bits, fp );
    buffer->bits = 0;
    buffer->bcount = 0;

    if ( shift < 0 ) {
      shift = BITS_PER_BYTE + shift;
      new_byte = shift >= 0 ? code << shift: code >> (shift * -1);

      buffer->bits = buffer->bits | new_byte;

      buffer->bcount += (BITS_PER_BYTE) - shift;
    }
  }
}

void flushBits( BitBuffer *buffer, FILE *fp ) {
  if ( buffer->bcount == 0 )
    return;
  else if ( buffer->bcount < 4 ) {
    write5Bits( 31, buffer, fp );
  }
  fputc( buffer->bits, fp );
}

int read5Bits( BitBuffer *buffer, FILE *fp ) {
  if ( feof( fp ) )
    return -1;

  int return_val = 0;

  if ( buffer->bcount < 5 ) {

    int ch = fgetc( fp );
    if ( ch < 0 )
      return -1;
    short newbcount = 8;
    unsigned char new_byte = ch;
  
    if ( buffer->bcount == 0 ) {
      buffer->bits = new_byte;
      newbcount  = 0;
    } else if ( buffer->bcount == 1 ) {
      buffer->bits |= new_byte >> 1;
      newbcount = 1;
    } else if ( buffer->bcount == 2 ) {
      buffer->bits |= new_byte >> 2;
      newbcount = 2;
    } else if ( buffer->bcount == 3 ) {
      buffer->bits |= new_byte >> 3;
      newbcount = 3;
    } else if ( buffer->bcount == 4 ) {
      buffer->bits |= new_byte >> 4;
      newbcount = 4;
    }
    //buffer->bits is saturated
    return_val = buffer->bits & 0xF8;
    shiftVal( &buffer->bits, 5 );
    buffer->bcount = 3;
    return_val = return_val >> 3;
    shiftVal( &new_byte, 5 - newbcount );
    if ( newbcount > 0 ) {
      if ( newbcount == 1 ) {
          new_byte &= 0x10;
      } else if ( newbcount == 2 ) {
          new_byte &= 0x18;
      } else if ( newbcount == 3 ) {
          new_byte &= 0x1C;
      } else if ( newbcount == 4 ) {
          new_byte &= 0x1E;
      }
      buffer->bits |= new_byte;
      buffer->bcount += newbcount;
    }
    return return_val;
    
  } else {
    return_val = buffer->bits & 0xF8;
    return_val = return_val >> 3;

    buffer->bcount -= 5;
    buffer->bits = buffer->bits << 5;

    return return_val;
  }
}

int read8Bits( BitBuffer *buffer, FILE *fp ) {
  int return_val = 0;

  if ( buffer->bcount < 8 ) {

    int ch = fgetc( fp );
    if ( ch < 0 )
      return -1;
    short newbcount = 8;
    unsigned char new_byte = ch;
  
    if ( buffer->bcount == 0 ) {
      buffer->bits = new_byte;
      newbcount  = 0;
    } else if ( buffer->bcount == 1 ) {
      buffer->bits |= new_byte >> 1;
      newbcount = 1;
    } else if ( buffer->bcount == 2 ) {
      buffer->bits |= new_byte >> 2;
      newbcount = 2;
    } else if ( buffer->bcount == 3 ) {
      buffer->bits |= new_byte >> 3;
      newbcount = 3;
    } else if ( buffer->bcount == 4 ) {
      buffer->bits |= new_byte >> 4;
      newbcount = 4;
    } else if ( buffer->bcount == 5 ) {
      buffer->bits |= new_byte >> 5;
      newbcount = 5;
    } else if ( buffer->bcount == 6 ) {
      buffer->bits |= new_byte >> 6;
      newbcount = 6;
    } else if ( buffer->bcount == 7 ) {
      buffer->bits |= new_byte >> 7;
      newbcount = 7;
    }
    //buffer->bits is saturated
    return_val = buffer->bits;
    shiftVal( &buffer->bits, 8 );
    buffer->bcount = 0;
    shiftVal( &new_byte, 8 - newbcount );
    buffer->bits = new_byte;
    buffer->bcount += newbcount;
        
    return return_val;
    
  } else {
    return_val = buffer->bits;

    buffer->bcount -= 8;
    buffer->bits = 0;

    return return_val;
  }
}

void shiftVal( unsigned char *val, int shift ) {
  *val = *val << shift;
}