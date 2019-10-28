
# include "sound.h"

////////////////////////////////////////////////////////////////////////////////

void init_sound() {

// Audio Initialization
Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ); // init sound

}
