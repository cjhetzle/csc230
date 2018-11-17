/**
  A struct to hold everything we need to define an activity

  @param title A pointer to the title of the activity
    which can be a string of an arbitrary length
  @param leader The string to hold the name of the leader
    which can be no longer than 20 chars
  @param start_hr The start hour (0-23)
  @param start_mn The start minute (0-59)
  @param end_hr The end hour (0-23)
  @param end_mn The end minute (0-59)
  @param ID The unique ID number given to each event, starting
    from 1 and incrementing up for each activity
*/
typedef struct {
  char *title;
  char leader[20];
  int startTime_h, startTime_m;
  int endTime_h, endTime_m;
  int id;
} Activity;

/**
  read activity will be responsible for taking user input
  and parsing it into usable information for creating
  a struct activity

  @return Activity * a pointer to the newly
   created Activity struct
*/
Activity *readActivity();

/**
  freeActivity is responsible for taking an Activity pointer
  and freeing its contents before freeing the pointer

  @param Activity * the activity pointer to free up
*/
void freeActivity( Activity *act );