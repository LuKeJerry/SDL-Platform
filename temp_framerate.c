

// Frame rate check - from:  http://www.libsdl.org/cgi/docwiki.cgi/Time_Examples

/*
Time Examples - Time based game loop

In a game loop you will want some kind of delay, to maintain a constant speed
and to ensure your program doesn't always use 99% of the processor.
This is a useful construct for maintaining a target framerate, rather than
aving a constant sleep time. Here the target interval is 30ms which equates
to 1000/30 = 33 frames per second.
*/


// Other infos on:
// http://stackoverflow.com/questions/2548541/achieving-a-constant-frame-rate-in-sdl
// http://books.google.co.uk/books?id=hiBFUv_FT0wC&pg=PA144&lpg=PA144&dq=game+programming+gems+ease+in+ease+out+interpolation&source=bl&ots=OBhLPzx42e&sig=UaVccnvd6S3oJFElqhRfzeosrig&hl=en&ei=i2OyS8-9OoKIsgPx5IXKAQ&sa=X&oi=book_result&ct=result&redir_esc=y#v=onepage&q&f=false


/*

#define TICK_INTERVAL    30 

static Uint32 next_time;

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}


// main game loop

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    while ( game_running ) {

        update_game_state();

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }
    
*/
