//
// PICK-the-virus - A simple 'one screen' platform engine in ANSI-C and SDL
////////////////////////////////////////////////////////////////////////////////

#include "timing.h"
#include "gfxvideo.h"
#include "phisics.h"
#include "sound.h"

////////////////////////////////////////////////////////////////////////////////

    // MAIN
int main(int argc, char *argv[]) {

    init_graphic();
    init_sound();

    load_background(); 

    center_sprite1(); // just put sprite1 at the screen center
    load_sprite1();

    game_loop();

    // Close SDL.  Normally, you'd free surfaces, but since 
    // SDL_SetVideoMode was used on buffer, SDL_Quit knows to
    // automatically free that for us.
  
    IMG_Quit();
    SDL_Quit(); 

    return 0;
} 
