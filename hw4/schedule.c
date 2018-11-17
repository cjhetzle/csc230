#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedule.h"

/**
  printActivity will print the values for the activity that was passed

  @param Activity *act the activity pointer to print
  @param int pad The amount to pad the leader name by
*/
void printActivity( Activity *act, int pad);
/**
  Conflict Leader will determine whether or not the given activity will create
  a schedule conflict for the leader by check the times for all their other
  activities already in the given schedule

  @param Schedule *sched The schedule to check the activities of
  @param Activity *act The activity you want to add with the leader you are checking for
  @return true, if the there is a conflict
*/
bool conflictLeader( Schedule *sched, Activity *act );

Schedule *createSchedule() {
  Schedule *sched = malloc( sizeof(Schedule) );

  sched->len = 0;
  sched->maxlen = 5;
  sched->nextID = 1;
  sched->acts = (Activity **)malloc( sizeof(Activity *) * sched->maxlen );

  return sched;
}

void freeSchedule( Schedule *sched ) {
  Activity **pntr = sched->acts;

  for ( int i = 0; i < sched->len; i++, pntr++ ) {
    freeActivity(*pntr);
  }

  free(sched->acts);

  free(sched);
}

bool addActivity( Schedule *sched, Activity *act ) {
  sched->len++;
  if ( sched->len > sched->maxlen ) {
    sched->acts = (Activity **)realloc( sched->acts, (sched->maxlen *= 2) * sizeof(Activity *) );
    if ( sched->acts == NULL )
      return false;
  }

  if ( conflictLeader( sched, act ) ) {
    sched->len--;
    return false;
  }

  act->id = sched->nextID;
  Activity **actList = sched->acts;

  //LETS DO SOME ORDERING!!!!

  for ( int i = 0; i < sched->len - 1; i++ ) {

    if ( act->startTime_h <= actList[i]->startTime_h ) {

      if ( act->startTime_h < actList[i]->startTime_h || 
        (act->startTime_h == actList[i]->startTime_h &&
        (act->startTime_m < actList[i]->startTime_m || 
        (act->startTime_m == actList[i]->startTime_m &&
         strcmp(act->leader, actList[i]->leader) < 0 ))) ) {

        Activity *temp1, *temp2;
  
        temp1 = actList[i+1];
        actList[i+1] = actList[i];
        actList[i] = act;
  
        for ( int j = i+2; j < sched->len; j++ ) {
          temp2 = actList[j];
          actList[j] = temp1;
          temp1 = temp2;
        }

        sched->nextID++;
        return true;
      } 
    }
  }

  sched->acts[sched->len - 1] = act;
  sched->nextID++;
  return true;
}

bool conflictLeader( Schedule *sched, Activity *act ) {
  char *leader = act->leader;
  int startTime = (act->startTime_h * 100) + act->startTime_m;
  int endTime = (act->endTime_h * 100) + act->endTime_m;
  Activity **pntr = sched->acts;

  for ( int i = 0; i < sched->len-1; i++) {
    if ( strcmp(leader, pntr[i]->leader) == 0 ) {
      int sT = (pntr[i]->startTime_h * 100) + pntr[i]->startTime_m;
      int eT = (pntr[i]->endTime_h * 100) + pntr[i]->endTime_m;

      if ( (endTime > sT && endTime <= eT) || (startTime < eT && startTime >= sT) )
        return true;
    }
  }

  return false;
}

bool removeActivity( Schedule *sched, int id ) {

  Activity **actList = sched->acts;

  for ( int i = 0; i < sched->len; i++ ) {
    if ( actList[i]->id == id ) {

      if ( sched->len == 1 ) {
        freeActivity(actList[0]);
      }

      for ( int j = i; j < sched->len - 1; j++ ) {
        if ( j == 0 )
          freeActivity(actList[j]);
        actList[j] = actList[j+1];
      }

      actList[sched->len-1] = NULL;
      sched->len--;
      return true;
    }
  }

  return false;
}

void printSchedule( Schedule *sched, bool (*test)( Activity *, void *arg ), void *arg ) {

  Activity **pntr = sched->acts;
  int longestName = 0;

  putchar('\n');

  for ( int i = 0; i < sched->len; i++, pntr++ ) {
    if ( test( *pntr, arg ) ) {
      if ( strlen((*pntr)->leader) > longestName )
        longestName = strlen((*pntr)->leader);
    }
  }


  pntr = sched->acts;
  for ( int i = 0; i < sched->len; i++, pntr++ ) {
    if ( test( *pntr, arg ) ) {
      printActivity( *pntr, longestName );
    }
  }
}

void printActivity( Activity *act, int pad ) {
  printf("%2d:%02d %2d:%02d (%03d) ", act->startTime_h, act->startTime_m, act->endTime_h, act->endTime_m, act->id );
  printf("%-*s ", pad, act->leader );
  printf("%s\n", act->title );
}