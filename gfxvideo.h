//
// HEADER - GRAPHICS and VIDEO functions
////////////////////////////////////////////////////////////////////////////////

    // INCLUDES
#include <stdbool.h>
#include "SDL/sdl.h"
#include "SDL/SDL_image.h"

   // GRAPHICS FUNCTIONS
void init_graphic();
void setvideobuffer();
void load_background();
void load_sprite1();
void center_sprite1();
void update_buffer();
void load_platform1();

SDL_Surface * SDL_ScaleSurface(SDL_Surface * Surface,
                                Uint16 OWidth,
                                Uint16 OHeight,
                                int sf);

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void zoom(char inout);
void set_sprite1(char direction, int number);


    // GLOBAL VARS
typedef struct {
    int w;
    int h;
    int bpp;
} _video;

_video video;  // video width,height,bit-per-pixel


SDL_Rect sprite1_cord; // = {0,0,18,20}; //x,y sprite plot coordinates - x,y size
SDL_Rect sprite1_src;  // =  {0,0,18,20}; // selecting the sprite from the bitmap-array
                       // INITIALIZATION VALUES MOVED TO center_sprite1() func - FIXME: remove from here!

int surf_scale;

///////////////////////////////////////////////////////////////////////////////
