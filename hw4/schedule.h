/**
  @file schedule.h
  @author Cameron Hetzler cjhetzle
*/
#include "activity.h"
#include <stdbool.h>

/**
  Struct for Schedule will hold a pointer list
  to all of the Activity structs it is managing

  @param Activity ** a pointer to all the Activity struct pointers
  @param int nextID the next id to assign the next Activity
  @param len the number of activities being managed
  @param maxlen the number of allocated spots
*/
typedef struct {
  Activity **acts;

  int nextID;

  int len;
  int maxlen;
  
} Schedule;

/**
  createschedule will initialize a schedule struct

  @return Schedule will return pointer of new schedule
*/
Schedule *createSchedule();

/**
  freeschedule will free each activity and the schedule pointer
  
  @param Schedule *sched The pointer to the schedule you want to free
*/
void freeSchedule( Schedule *sched );

/**
  addActivity will add a new Activity pointer to the struct Schedule passed in

  @param Schedule *sched the Schedule you want to add to
  @param Activity *act the Activity pointer you want to add
  @return bool, true if it was successful
*/
bool addActivity( Schedule *sched, Activity *act );

/**
  removeActivity will remove the activity pointer with
  the specified id number from the given Schedule pointer

  @param Scedule to remove from
  @param Activity to remove
  @return true, if it was succesful
*/
bool removeActivity( Schedule *sched, int id );

/**
  printSchedule will print all the activities it is managing in the correct order

  @param Schedule *sched the schedule to print activities from
  @param bool (test *)( Activity *, void *arg) a pointer to a function to call
  @param void *arg a void pointer to the filter value to pass to the function
*/
void printSchedule( Schedule *sched, bool (*test)( Activity *, void *arg ), void *arg );