
#include <iostream>
#include <SDL/sdl.h>
#include"main_menu.h"
#include"level_ko_sabai_kaam_herne_file.h"
 using namespace std;

int main(int argc, char* argv[])
{
    int quit=0;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *screen = SDL_SetVideoMode(1366, 768, 32, SDL_SWSURFACE|SDL_RESIZABLE);
    screen = SDL_SetVideoMode(1366, 768, 32, SDL_SWSURFACE|SDL_RESIZABLE|SDL_FULLSCREEN);
    main_menu m(screen); level l(screen);
    //m("new_image.bmp", "new_glow_image.bmp", 105, 83, 325, 32);

    while(m.selection!=4)
    {
       // main_menu m(screen); level l(screen);
    m.show();
    l.show_level( m.selected_level());
    }
   // SDL_Delay(10000);
    return 0;
}
