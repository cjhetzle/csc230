#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
} Activity;

typedef struct {
  Activity **acts;
  int nextID;
} Schedule;

int len = 5;
Activity **pntr;

int main() {

  Schedule *sched = (Schedule *)malloc( sizeof(Schedule) );

  sched->acts = (Activity **)malloc( sizeof(Activity *) * len );

  pntr = sched->acts;
  for ( int i = 0; i < len; i++, pntr++ ) {
    (*pntr) = (Activity *)malloc( sizeof(Activity) );
    (*pntr)->id = sched->nextID++;
  }

  pntr = sched->acts;
  for( int i = 0; i < len; i++, pntr++ ) {
    printf("%d\n", (*pntr)->id );
  }


  pntr = sched->acts;
  for ( int i = 0; i < len; i++, pntr++ ) {
    free((*pntr));
  }

  free(sched->acts);
  free(sched);



  return 0;
}