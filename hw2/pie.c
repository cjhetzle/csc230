/**
    @file pie.c
    @author Cameron Hetzler (cjhetzle)

    This program reads a file of color values and writes an image file
    that depicts those values in a pie chart
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/** a hard set value for the axis of the picture */
#define AXIS 49.5
/** the size of the image */
#define IMG_SIZE 100
/** the radius of the inner pie chart */
#define RAD 45

/** global variables for the degrees of all colors, used in main and insideSlice */
double d_red, d_green, d_blue;

/*
  Checks to see if the corrodinate is inside the circle of radius rad
  @param x The x corrordinate
  @param y The y corrordinate
  @param rad the radius of the circle

  @return true if point is in the circle
*/
bool insideCircle( int x, int y, int rad ) {

  //distance formula
  // (xdiff^2 + ydiff^2)^.5
  float xdiff = x - AXIS;
  float ydiff = y - AXIS;
  if (xdiff < 0) {
    xdiff = xdiff * -1;
  }
  if (ydiff < 0) {
    ydiff = ydiff * -1;
  }
  xdiff = pow(xdiff, 2);
  ydiff = pow(ydiff, 2);
  float length = xdiff + ydiff;
  length = pow(length, 0.5);

  if (length <= rad) {
    return true;
  }
  return false;
}

/*
  Checks to see if the point is inside of a slice
  @param x X coordinate
  @param y Y coordinate
  @param color the Colored slice to check

  @return true if point is inside the area of the desired color
*/
bool insideSlice( int x, int y, int color ) {
  double angle = atan2(y - AXIS, x - AXIS);
  //printf("%1.3f ", angle);
  angle += M_PI;

  if (color == 0) {
    //red
    if (d_red > 0 && angle >= 0 && angle <= d_red) {
      return true;
    }
  } else if (color == 1) {
    //green
    if (d_green > 0 && angle > d_red && angle <= d_green) {
      return true;
    }
  } else if (color == 2) {
    //blue
    if (d_blue > 0 && angle > d_green && angle < 2 * M_PI) {
      return true;
    }
  }

  return false;
}

/*
  calculates and prints the color of each pixel in a 100x100 picture to draw a pie chart

  @return returns the exit status of the program
*/
int main() {
  int full_color = 255;
  int v_red, v_green, v_blue, total;
  int result = 0;
  //receives the VALUE of each color
  result += scanf("%d", &v_red);
  result += scanf("%d", &v_green);
  result += scanf("%d", &v_blue);

  //printf("%d", result);
  //did not load all numbers, exit with status 100
  if (result != 3 || v_red < 0 || v_green < 0 || v_blue < 0) {
    printf("Invalid input\n");
    exit(100);
  }

  //find the total amount of color to divide by
  total = v_red + v_green + v_blue;
  if (total == 0) {
    printf("Invalid input\n");
    exit(100);
  }
  //calculates the PERCENTAGE of each color
  double p_red, p_green, p_blue;
  p_red = (double)v_red / total;
  p_green = (double)v_green / total;
  p_blue = (double)v_blue / total;

  //Calculates the DEGREES of the angles for each slice in radians
  //since each angle in the circle grows off the previous we add
  //the previous angle to the next one
  d_red = p_red * 2 * M_PI;
  d_green = p_green * 2 * M_PI;
  d_green += d_red;
  d_blue = p_blue * 2 * M_PI;
  d_blue += d_green;

  //three lined header
  printf("P3\n%d %d\n255\n", IMG_SIZE, IMG_SIZE);

  //Nested for loop that goes by column J and row I
  //it first checks to see if the point is in the smaller circle
  //of the graph, if so it then calls insideSlice to check
  //if its in a proportioned slice of the graph and draws the cooresponding
  //color. If its not in the inside circle it checks to see if its
  //in a circle that has a 3 pixel longer radius (border length) and draws black if so.
  //if it doesn't fit into any of those it will draw a white pixel
  for (int i = 0; i < IMG_SIZE; i++) {
    for (int j = 0; j < IMG_SIZE; j++) {
      if (insideCircle(j, i, RAD)) {
        if (insideSlice(j, i, 0)) {
          //inside of RED
          printf("%3d %3d %3d ", full_color, 0, 0);
        } else if (insideSlice(j, i, 1)) {
          //inside of GREEN
          printf("%3d %3d %3d ", 0, full_color, 0);
        } else if (insideSlice(j, i, 2)) {
          //inside of BLUE
          printf("%3d %3d %3d ", 0, 0, full_color);
        } else {
          printf("%3d %3d %3d ", full_color, full_color, full_color);
        }
      } else if (insideCircle(j, i, RAD + 3)) {
        //draw BLACK
        printf("%3d %3d %3d ", 0, 0, 0);
      } else {
        //draw WHITE
        printf("%3d %3d %3d ", full_color, full_color, full_color);
      }
    }
    printf("\n");
  }


  return 0;
}
