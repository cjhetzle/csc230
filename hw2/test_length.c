#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define AXIS 49.5

_Bool insideCircle( int x, int y, int rad ) {
  //distance formula

  // (xdiff^2 + ydiff^2)^.5

  float xdiff = x - AXIS;
  float ydiff = y - AXIS;
  xdiff = pow(xdiff, 2);
  ydiff = pow(ydiff, 2);
  float length = xdiff + ydiff;
  length = pow(length, 0.5);

  if (length <= rad) {
    return true;
  }
  return false;
}

int main() {
  
  int x = 0, y = 0;

  scanf("%d", &x);
  scanf("%d", &y);

  if (insideCircle(x, y, 48)) {
    printf("True");
  } else {
    printf("False");
  }
  

  return 0;
}