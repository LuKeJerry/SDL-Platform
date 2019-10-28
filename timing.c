// 
// TIMING & FRAME-PER-SECOND CONTROL + GAME_LOOP
////////////////////////////////////////////////////////////////////////////////

#include "timing.h"
#include "phisics.h"  // superkeyboardcheck() , phisics_check(), etc...
#include "gfxvideo.h" // update_buffer() and so on...

////////////////////////////////////////////////////////////////////////////////

Uint32 time_left(void) {

    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}


void game_loop() {

    done = false;

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    while ( !done )
    {
        superkeyboardcheck();

    	phisics_check();

    	check_jump();
		sprite1_move();

		update_buffer();

		// trying to limit framerate to specific FPS (see TICK_INTERVAL)
		SDL_Delay(time_left());
        next_time += TICK_INTERVAL;

    }
}
