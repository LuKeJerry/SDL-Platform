//
// HEADER - PHISICS and MOVEMENTS + KEYBOARD CONTROL (at the moment)
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////


    // PHISICS and MOVEMENTS
void check_jump();
void sprite1_fall();
void sprite1_move(); // maybe we could move inside here the fall and jump too
void phisics_check();

   // JOY & KEYBOARD CONTROL
void superkeyboardcheck();

 
  // GLOBAL VARS 
static unsigned int fallidx; // falling index counnter
                             // global as it's used both by check_jump() and sprite1_fall() functions

static unsigned int sprite1_xspeed  = 0; // 0 = stop 1-10=speed left 11-20=speed right
                                         // global as it's used both by superkeyboardcheck() and sprite1_move() functions

static bool jumping        = false;
static bool jumping_break  = false;
static bool on_platform    = false;
static bool on_a_rightwall = false;
static bool on_a_leftwall  = false;
