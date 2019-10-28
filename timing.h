//
// HEADER - TIMING & FRAME-PER-SECOND CONTROL
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>  // bool
#include "SDL/SDL.h"  // Uint32



#define TICK_INTERVAL	17  // (1000 / 17 = ~60 FPS) - (1000 / 10 = 100 FPS) - 8 ~120 FPS 
// FIXME: the above interval is extremely high because of badly implemented
// jump and fall functions: using values of 0 to skip movement of sprite1
// might be a waste of screen refreshes and CPU time (very important for
// Amiga 68K port)

////////////////////////////////////////////////////////////////////////////////

    // GLOBAL VARS
bool done;         // when true the game quits
Uint32 next_time;  // Used in time_left() ... 

    // TIMING
void game_loop();
Uint32 time_left(void); // ...to set a fixed FPS speed
