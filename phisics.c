//
// PHISICS and MOVEMENTS + KEYBOARD CONTROL (at the moment)
////////////////////////////////////////////////////////////////////////////////

#include "SDL/sdl.h"

#include "phisics.h"
#include "gfxvideo.h"
#include "timing.h" 

////////////////////////////////////////////////////////////////////////////////

void phisics_check() {

// printf("Sprite1 x,y: %d-%d\n", sprite1_cord.x / surf_scale, sprite1_cord.y / surf_scale);

        // stay on platforms //FIXME: Update platform coordinates
        if(!jumping &&
           !(
            (
            (sprite1_cord.y > 121 * surf_scale) &&
            ((sprite1_cord.x < 214 * surf_scale) && (sprite1_cord.x > 96 * surf_scale) )
            )
            ||
            (
            (sprite1_cord.y > 137 * surf_scale) && (sprite1_cord.y < 139 * surf_scale) && (sprite1_cord.x > 6 * surf_scale)
            )
            ||
            (
            (sprite1_cord.y > 154 * surf_scale) && (sprite1_cord.y < 156 * surf_scale) && (sprite1_cord.x > 24 * surf_scale)
            )
            ||
            (
            (sprite1_cord.y > 162 * surf_scale)
            )
           )
          )
            // real platform coordinate -20px for sprite height or -18 for width
        {
            on_platform = false;
            sprite1_fall();
        }
        else
        {
            on_platform = true;
        }

        // don't walk through RIGHT walls
        if
        (
            (
            (sprite1_cord.y > 122 * surf_scale) && (sprite1_cord.y <= 138 * surf_scale)
            && (sprite1_cord.x < 97 * surf_scale) && (sprite1_cord.x > 95 * surf_scale)
            )
        ||
            (
            (sprite1_cord.y > 156 * surf_scale) && (sprite1_cord.y <= 163 * surf_scale)
            && (sprite1_cord.x < 25 * surf_scale) && (sprite1_cord.x > 23 * surf_scale)
            )
        ||
            (
            (sprite1_cord.y > 139 * surf_scale) && (sprite1_cord.y <= 155 * surf_scale)
            && (sprite1_cord.x < 81 * surf_scale) && (sprite1_cord.x > 79 * surf_scale)
            )
        )

        {
            on_a_rightwall = true;
        }
        else
            on_a_rightwall = false;


        // don't walk through LEFT walls
        if (
        (sprite1_cord.y > 122 * surf_scale) && (sprite1_cord.y <= 138 * surf_scale)
        && (sprite1_cord.x > 213 * surf_scale) && (sprite1_cord.x < 215 * surf_scale)
        )
        {
            on_a_leftwall = true;
        }
        else
            on_a_leftwall = false;

}

void sprite1_move() {

//static int sprite1_pos[11] = {1,1,1,3,3,3,1,1,1,2,2,2}; // trying to stretch this to slow down
static int sprite1_pos[24] = {1,1,1,1,1,1,3,3,3,3,3,3,1,1,1,1,1,1,2,2,2,2,2,2};

static int x;

    switch (sprite1_xspeed)
    {
        case 11: // move right
            if ( (!jumping) && (on_platform) )
            {
                set_sprite1('r',sprite1_pos[x]);
                if (x>=23) x=0;
                else x++;
            }
            else set_sprite1('r',1);

            if ((sprite1_cord.x < 302 * surf_scale) // just don't go out of the right border
                && (!on_a_rightwall)) // also don't go through walls
                sprite1_cord.x = sprite1_cord.x + ( 1 * surf_scale );
            break;

        case 1: // move left
            if ( (!jumping) && (on_platform) )
            {
                set_sprite1('l',sprite1_pos[x]);
                if (x>=23) x=0;
                else x++;
            }
            else set_sprite1('l',1);


            if ((sprite1_cord.x > 0) // just don't go out of the left border
                && (!on_a_leftwall)) // also don't go through walls
                sprite1_cord.x = sprite1_cord.x - ( 1 * surf_scale );

            break;

        case 0:
            break;
    }

}



void check_jump() {

static int jumpidx = 0;

const int jumptable[40] = {1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0};

    if (jumping)
    {

        if (jumpidx <= 39)
        {
            sprite1_cord.y = sprite1_cord.y - (jumptable[jumpidx] * surf_scale);
            jumpidx++;
            if (jumpidx > 38) fallidx = 0; // max jumping reached, so reset the fall index to 0 (?)
            if (jumping_break) // the KUY_UP has been released, stop jumping...
            {
               fallidx = jumpidx; // ... and start falling from the point we reached
               jumping = false;
               jumpidx = 0; // also we reset "jumpidx" so that next jump can still be full up
            }
        }
        else
        {
            jumping = false;  // we reached the maximum jump height, start falling slowly now
            jumpidx = 0; // re-setting the "i" jump index to 0 so we can jump again :)
        }
    }
}


void sprite1_fall() {

// int falltable[40] = {1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0};
const int falltable[40] = {0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1};

    if (fallidx<=19)  // falling with some initial acceleration...
        {
            sprite1_cord.y = sprite1_cord.y + ( falltable[fallidx] * surf_scale );
            fallidx++;
        }
        else
        {
            sprite1_cord.y = sprite1_cord.y + ( 1 * surf_scale ); // ... then falling normally
        }

        jumping_break = false; // we can break the jumps again
}



// Keyboard input in SDL
// need to avoid multiple jumpings (flying) and check key releases
// see: http://www.libsdl.org/docs/html/guideinputkeyboard.html
//  and for keykodes: http://wiki.libsdl.org/moin.cgi/SDL_Keycode

void superkeyboardcheck() {

SDL_Event event;

		while ( SDL_PollEvent ( &event ) )
        {
            switch( event.type )
            {

                case SDL_QUIT:  //Look for window exit gadget [X]
                    done = true;
                    break;

                // Look for a keypress
                case SDL_KEYDOWN:
                // Check the SDLKey value
                switch( event.key.keysym.sym ){

                    case SDLK_LEFT:
                        sprite1_xspeed = 1;
                        break;

                    case SDLK_RIGHT:
                        sprite1_xspeed = 11;
                        break;

                    case SDLK_UP:
                        if (on_platform)
                        {
                            jumping = true;
                        }
                        break;

                    case SDLK_DOWN:
                        // do something when down-arrow is pushed
                        break;

                    case SDLK_ESCAPE:
                        done = true;
                        break;

                    case SDLK_F2:
                        zoom('o');
                        break;

                    case SDLK_F3:
                        zoom('i');
                        break;

                    case SDLK_F4:
                        zoom('f');
                        break;

                    case SDLK_F9: // just for debugging
                        printf("Sprite1 absolute source x,y: %d-%d\n", sprite1_src.x / surf_scale, sprite1_src.y / surf_scale);
                        printf("Sprite1 relative source x,y: %d-%d\n", sprite1_src.x, sprite1_src.y);
                        break;

                    case SDLK_F10: // just for debugging
                        printf("Sprite1 absolute x,y: %d-%d\n", sprite1_cord.x / surf_scale, sprite1_cord.y / surf_scale);
                        printf("Sprite1 relative x,y: %d-%d\n", sprite1_cord.x, sprite1_cord.y);
                        break;

                    default:
                        break;

                }
                break;


             case SDL_KEYUP:
                switch( event.key.keysym.sym ){

                    case SDLK_LEFT:
                        if( sprite1_xspeed > 0 )
                        {
                            sprite1_xspeed = 0;
                            set_sprite1('l',1);  // reset sprite status-1-left
                        }
                        break;

                    case SDLK_RIGHT:
                        if( sprite1_xspeed > 0 )
                        {
                            sprite1_xspeed = 0;
                            set_sprite1('r',1); // reset sprite status-1-right
                        }
                        break;

                    case SDLK_UP: // we want to stop the jumping up when UP key is released
                        if (jumping)
                        {
                            jumping_break = true;
                        }
                        break;

                    case SDLK_DOWN:
                        // do something when down-arrow is released
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
            }
        }

}
