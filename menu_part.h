
#include <SDL/sdl.h>

class menu_part
{
  protected:
        SDL_Surface* image;
        SDL_Surface* glowing_image;
        int x, y , height, width;
    public:
        menu_part(){}
        //menu_part(SDL_Surface* img, SDL_Surface* glow_img, int a, int b):image(img), glowing_image(glow_img), x(a), y(b) {}
        void set_image (char* s, char* t, unsigned int a=0, unsigned int b=0, unsigned int wide=5, unsigned int hite=5)
        {
            image= SDL_LoadBMP(s);
            glowing_image= SDL_LoadBMP(t);
            x= a; y= b; height= hite; width= wide;
        }

        bool is_mouse_over(unsigned int mouse_x, unsigned int mouse_y) //checks in any menu part mouse is or not
        {
            if(mouse_x>x && mouse_y>y && mouse_x<x+width && mouse_y<y+height) return true;
            else return false;
        }

        void display(SDL_Surface* screen)
        {
            SDL_Rect rect; rect.x=x; rect.y=y;
            SDL_BlitSurface(image, NULL, screen, &rect);//displays default image ie mouse is not pointing that image
        }
        void display_glow(SDL_Surface* screen)
        {
            SDL_Rect rect; rect.x=x; rect.y=y;
            SDL_BlitSurface(glowing_image, NULL, screen, &rect); //display glowing image when mouse is pointing
        }

        void colour_udaune(unsigned int r, unsigned int g, unsigned int b) //removes any color here background
        {
            SDL_SetColorKey(image, SDL_SRCCOLORKEY ,SDL_MapRGB (image->format ,r,g,b) );
            SDL_SetColorKey(glowing_image, SDL_SRCCOLORKEY ,SDL_MapRGB (glowing_image->format ,r,g,b) );
        }

        ~menu_part(){}
};
