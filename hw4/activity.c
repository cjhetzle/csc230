/**
  @file activity.c
  @author Cameron Hetzler cjhetzle

  Activity.c will deal with all the functions needed to manage
   and manipulate with the Activity struct
*/
#include "activity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** getTitle is meant to dynamically allocate memory
 and insert the name of the activities title */
char *getTitle();

Activity *readActivity() {

  int startTime_h, startTime_m, endTime_h, endTime_m;
  char leader[20] = {};
  char *title;

  if ( !scanf("%d : %d %d : %d %20s ", &startTime_h, &startTime_m,
      &endTime_h, &endTime_m, leader) ) {
    //invalid
    return NULL;
  }

  title = getTitle();

  if ( title == NULL ||
    (startTime_h > 23 || startTime_h < 0) || 
    (startTime_m > 59 || startTime_m < 0) ||
    (endTime_h > 23 || endTime_h < 0) ||
    (endTime_m > 59 || endTime_m < 0) ||
    (startTime_h > endTime_h) ||
    (startTime_h == endTime_h && startTime_m > endTime_m) ) {
    free(title);
    return NULL;
  }

  Activity *act = (Activity *)malloc( sizeof(Activity) );

  act->startTime_h = startTime_h;
  act->startTime_m = startTime_m;
  act->endTime_h = endTime_h;
  act->endTime_m = endTime_m;
  strcpy(act->leader, leader);
  act->title = title;

  return act;
}

char *getTitle() {
  int maxlen = 10;
  char *title = calloc( maxlen, 1 );

  int i = 0; char c;
  while ( (c = fgetc(stdin)) != '\n' ) {
    title[ i++ ] = c;

    if ( i >= maxlen ) {
      maxlen *= 2;
      title = realloc( title, maxlen );
    }
  }

  title[ i ] = '\0';

  return title;
}

void freeActivity( Activity *act ) {
  free(act->title);
  free(act);
}