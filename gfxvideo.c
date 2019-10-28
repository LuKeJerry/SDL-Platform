//
// GRAPHICS and VIDEO functions
////////////////////////////////////////////////////////////////////////////////

    // INCLUDES
#include "gfxvideo.h"
#include "SDL/sdl.h"

   // GLOBAL VARS
bool fullscreen = false;

SDL_Surface * buffer      = NULL;
SDL_Surface * bg_image    = NULL;
SDL_Surface * sprite1     = NULL;
SDL_Surface * platform1   = NULL;
SDL_Surface * tmp_surf    = NULL;

////////////////////////////////////////////////////////////////////////////////


void init_graphic() {

    //Start SDL
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO); // SDL_INIT_JOYSTICK

    // Set window caption
    SDL_WM_SetCaption( "Pick-the-virus!", NULL );

    // Set window icon
    SDL_Surface * wmicon;

        if (wmicon = IMG_Load("gfx/icon.png"))
        {
            SDL_WM_SetIcon(wmicon, NULL);
            SDL_FreeSurface(wmicon);
        }

    // Disable mouse cursor
    SDL_ShowCursor(SDL_DISABLE);
    
    surf_scale = 2; // default scale is 2x

    // Set the videobuffer
    setvideobuffer();

}


void setvideobuffer() {

    video.w = 320;
    video.h = 200;
    video.bpp = 32;

    if ( fullscreen == true )   // For fullscreen we use 1x graphics
    {
        surf_scale = 2; // scale for full-screen mode
        buffer = SDL_SetVideoMode( 640, 400, video.bpp, SDL_SWSURFACE | SDL_FULLSCREEN );
    }
    else                        // For windowed

        buffer = SDL_SetVideoMode( video.w * surf_scale, video.h * surf_scale, video.bpp, SDL_SWSURFACE );

}


void load_background() {

   // temporary moved as global... doesn't look so nice anyway :(
   // SDL_Surface *bg_image = SDL_LoadBMP("gfx\\montezuma_background_1.bmp");
   // bg_image = SDL_LoadBMP("gfx\\montezuma_background_1.bmp");
   // bg_image = IMG_Load("gfx\\montezuma_background_1.png");


   // Converting the loaded image to the pixel format and colors of the video framebuffer
   tmp_surf = IMG_Load("gfx/montezuma_background_1.png");
   bg_image = SDL_DisplayFormatAlpha(tmp_surf);
   SDL_FreeSurface(tmp_surf);

   // do this if you want to scale up the images
   bg_image = SDL_ScaleSurface(bg_image, video.w, video.h, surf_scale);

}

void load_sprite1() {

   // adjusting width,height according to the scale rate
   sprite1_src.w = 18 * surf_scale;
   sprite1_src.h = 20 * surf_scale;


   //SDL_Surface *sprite1 = SDL_LoadBMP("gfx\\montezuma_sprite_array.bmp");
   // sprite1 = IMG_Load("gfx\\montezuma_sprite_array.png");

   tmp_surf = IMG_Load("gfx/montezuma_sprite_array_alpha.png");
   sprite1 = SDL_DisplayFormatAlpha(tmp_surf);
   SDL_FreeSurface(tmp_surf);

   sprite1 = SDL_ScaleSurface(sprite1, 54, 40, surf_scale);

}


void center_sprite1() {

    //sprite1_src  = {0,0,18,20};

    // selecting the sprite from the bitmap-array
    sprite1_src.x = 0;
    sprite1_src.y = 0;
    sprite1_src.w = 18;
    sprite1_src.h = 20;

    // sprite1_cord = {0,0,18,20};

    // FIXME: remove the above-below sprite1_cord double assignment

    // positioning the sprite1 in the middle of the screen
    sprite1_cord.x = (video.w / 2) * surf_scale; 
    sprite1_cord.y = (video.h / 2) * surf_scale; 
    sprite1_cord.w = 18;
    sprite1_cord.h = 20;

}



void load_platform1() {

    // platform1 = SDL_LoadBMP("gfx\\platform_1.bmp");

    // Set pink as transparent for platform1
    // Uint32 colorKey = SDL_MapRGB( platform1->format, 0xFF, 0, 0xFF );
    // SDL_SetColorKey(platform1, SDL_SRCCOLORKEY, colorKey );
    
}


void update_buffer() {

    // Redraw background and sprite1
    SDL_BlitSurface(bg_image,        NULL, buffer, NULL);
    SDL_BlitSurface(sprite1, &sprite1_src, buffer, &sprite1_cord);
    //SDL_BlitSurface(platform1,       NULL, buffer, &platform1_cord);

    SDL_Flip ( buffer );
    
}


SDL_Surface * SDL_ScaleSurface(SDL_Surface* Surface, Uint16 OWidth, Uint16 OHeight, int sf) {
                                // surface to scale, original width, height, scale factor

    int xs = 0;
    int ys = 0;
    int o_x = 0;
    int o_y = 0;
    Uint32 pixel;

    int _stretch_factor_x = sf; // later on remove this and just use sf
    int _stretch_factor_y = sf; // same as above

    SDL_Surface * _ret = SDL_CreateRGBSurface(Surface->flags,
                                              (OWidth * sf),
                                              (OHeight * sf),
                                              Surface->format->BitsPerPixel,
                                              Surface->format->Rmask,
                                              Surface->format->Gmask,
                                              Surface->format->Bmask,
                                              Surface->format->Amask);


    if(!Surface || !OWidth || !OHeight)
    {
        printf("Error in SDL_ScaleSurface, one of the parameter was null!\n");
        return 0;
    }



    SDL_LockSurface(Surface);
    SDL_LockSurface(_ret);

    for (ys = 0; ys < OHeight; ys++) //Run across all Y pixels.
        for(xs = 0; xs < OWidth; xs++) //Run across all X pixels.
            {

            pixel = getpixel(Surface, xs, ys);
            //pixel = 8437952;

            for(o_y = 0; o_y < _stretch_factor_y; ++o_y) //Draw _stretch_factor_y pixels for each Y pixel.
                for(o_x = 0; o_x < _stretch_factor_x; ++o_x) //Draw _stretch_factor_x pixels for each X pixel.
                {
                    putpixel(_ret,
                             (_stretch_factor_x * xs) + o_x,
                             (_stretch_factor_y * ys) + o_y,
                             pixel);
                    //printf("The pixel is: %d, should be: %d - put at x,y: %d-%d\n",  pixel ,  SDL_MapRGB(_ret->format , 96, 64, 0), (_stretch_factor_x * xs) + o_x, (_stretch_factor_y * ys) + o_y  );
                }
            }

    SDL_UnlockSurface(_ret);
    SDL_UnlockSurface(Surface);

    return _ret;

}


Uint32 getpixel(SDL_Surface *surface, int x, int y) {

    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;


    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        // printf("Getpixel returns: %d - fox x,y: %d-%d\n", *(Uint32 *)p , x , y);
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {

    int bpp = surface->format->BytesPerPixel ;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;


    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


void zoom(char inout) {

    int previous_scale;

    previous_scale = surf_scale;

    switch (inout) {

        case ('i'): // zoom-in
            if ((surf_scale < 4) && (fullscreen == false)) surf_scale++;
            break;

        case ('o'): // zoom-out
            if ((surf_scale > 1) && (fullscreen == false)) surf_scale--;
            break;

        case ('f'): // fullscreen
            surf_scale = 2;
            fullscreen = !fullscreen;
            break;
    }

    setvideobuffer();

    // reload the background according to the scale
    load_background();

    // update the sprite coordinates according to the scale
    sprite1_cord.x = (sprite1_cord.x / previous_scale) * surf_scale;
    sprite1_cord.y = (sprite1_cord.y / previous_scale) * surf_scale;

    sprite1_src.x = (sprite1_src.x / previous_scale) * surf_scale;
    sprite1_src.y = (sprite1_src.y / previous_scale) * surf_scale;

    // reload the sprite according to the scale
    load_sprite1();

}


void set_sprite1(char direction, int number) { // FIXME: check if SDL has some function to flip horizontally graphics

    switch (direction)
    {
        case 'r':
            switch (number)
            {
                case 1:
                sprite1_src.x = 0 * surf_scale; // sprite right-1
                sprite1_src.y = 0 * surf_scale; // sprite right-1
                break;

                case 2:
                sprite1_src.x = 18 * surf_scale; // sprite right-2
                sprite1_src.y = 0  * surf_scale;  // sprite right-2
                break;

                case 3:
                sprite1_src.x = 36 * surf_scale; // sprite right-3
                sprite1_src.y = 0  * surf_scale;  // sprite right-3
                break;
            }
            break;

        case 'l':
            switch (number)
            {
                case 1:
                sprite1_src.x = 0  * surf_scale ;  // sprite left-1
                sprite1_src.y = 20 * surf_scale;   // sprite left-1
                break;

                case 2:
                sprite1_src.x = 18 * surf_scale; // sprite left-2
                sprite1_src.y = 20 * surf_scale; // sprite left-2
                break;

                case 3:
                sprite1_src.x = 36 * surf_scale; // sprite left-3
                sprite1_src.y = 20 * surf_scale; // sprite left-3
                break;
            }
            break;
    }
}


