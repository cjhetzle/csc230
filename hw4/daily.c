/**
  @file daily.c
  @author Cameron Hetzler

  The main implementation file to manage a calendar
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "schedule.h"

/** preprocessor definitions for keywords to look for */
#define ADD "add"
/** preprocessor definitions for keywords to look for */
#define REMOVE "remove"
/** preprocessor definitions for keywords to look for */
#define SCHEDULE "schedule"
/** preprocessor definitions for keywords to look for */
#define LEADER "leader"
/** preprocessor definitions for keywords to look for */
#define AT "at"
/** preprocessor definitions for keywords to look for */
#define MATCH "match"
/** preprocessor definitions for keywords to look for */
#define QUIT "quit"

/** This method will check for user input and call the correct functions */
void UserCommand();
/** calling this will free all the memory in the program */
void freeMemory();
/**
  reTurn will return true

  @param Activity *act Ignored Activity pointer
  @param void *arg the filter that's ignored
  @return true
*/
bool reTrue( Activity *act, void *arg );
/**
  atTime will check if the given function is occuring during
  a specific time

  @param Activity *act the activity in question
  @param void *arg the pointer to the time
  @return true if the activity occurs at the time
*/
bool atTime( Activity *act, void *arg );
/**
  isLeader checks to see if the Activity in question
  has the given leader

  @praam Activity *act The activity pointer in question
  @param void *arg the pointer to the char * for the leader
  @return true if the Activity leader is the same as the one passed in
*/
bool isLeader( Activity *act, void *arg );
/**
  isMatch will check to see if the string passed in is a substring of
  the activity title

  @param Activity *act The activity in question
  @param void *arg the pointer to the string to match
  @return true is the string passed in is a substring of the title
*/
bool isMatch( Activity *act, void *arg );
/**
  Error will print the given error and flush the stdin

  @param char*error the error to print
*/
void Error( char *error );
/** the schedule struct pointer to use for the program */
Schedule *sched;
/**
  The start of the program and will loop usercommand indefinitely until
  the program is exited from inside the function

  @return int the error code for the program
*/
int main() {

  sched = createSchedule();

  atexit(freeMemory);

  for(;;) {

    UserCommand();

  }

  return 0;
}

void freeMemory() {
  freeSchedule(sched);
}

void UserCommand() {
  char cmd[10] = {};

  printf("> ");

  if ( !scanf("%10s", cmd) ) {
    Error("Invalid command");
    return;
  }

  if ( strcmp(cmd, ADD) == 0 ) {

    Activity *act = readActivity();

    if ( act == NULL ) {
      printf("Invalid command\n");
      return;
    }

    if ( !addActivity( sched, act ) ) {
      freeActivity( act );
      printf("Schedule conflict\n");
    }
  } else if ( strcmp(cmd, REMOVE) == 0 ) {
    int id;

    if ( !scanf("%d", &id ) ) {
      Error("Invalid command");
      return;
    }

    if ( !removeActivity( sched, id ) ) {
      Error("Invalid command");
    }
  } else if ( strcmp(cmd, SCHEDULE) == 0 ) {

    printSchedule( sched, &reTrue, NULL);
  } else if ( strcmp(cmd, LEADER) == 0 ) {

    char leader[20] = {};

    if ( !scanf("%s", leader) || strlen(leader) > 20 ) {
      Error("Invalid command");
      return;
    }

    printSchedule( sched, &isLeader, leader );
  } else if (strcmp(cmd, AT) == 0 ) {
    int times[2];

    if ( !scanf("%d : %d", &times[0], &times[1]) ||
      (times[0] > 23 || times[0] < 0) ||
      (times[1] > 59 || times[1] < 0) ) {
      Error("Invalid command");
      return;
    }

    printSchedule( sched, &atTime, times );
  } else if (strcmp(cmd, MATCH) == 0 ) {
    char *match = (char *)calloc( 20, 1);

    if ( !scanf("%s", match) ) {
      Error("Invalid command");
      return;
    }
    
    printSchedule( sched, &isMatch, match );
    free(match);
  } else if (strcmp(cmd, QUIT) == 0 ) {
    //freeMemory(sched);
    exit(0);
  } else {
    if ( feof(stdin) ) {
      exit(0);
    }
    Error("Invalid command");
  }
}

void Error( char *error ) {
  printf("%s\n", error);
  while (getchar() != '\n');
}

bool isMatch( Activity *act, void *arg ) {
  if (strcasestr( act->title, arg))
    return true;
  else
    return false;
}

bool isLeader( Activity *act, void *arg ) {
  char *leader = (char *)arg;

  if ( strcmp(leader, act->leader) == 0 )
    return true;
  return false;
}

bool atTime( Activity *act, void *arg ) {
  int *times = (int *)arg;
  int time = (*times * 100) + times[1];
  int startTime = (act->startTime_h * 100) + act->startTime_m;
  int endTime = (act->endTime_h * 100) + act->endTime_m;

  if ( time >= startTime && time < endTime ) {
    return true;
  }

  return false;
}

bool reTrue( Activity *act, void *arg ) {

  return true;
}