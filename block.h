
#include<SDL/sdl.h>

class block:public menu_part
{
  private:

        static SDL_Surface *zero, *one, *two, *three, *four, *five, *flag, *mine;

  public:
        static int width, height;
        int value;
        bool is_clicked;
        bool is_flagged;

        block(): value(0), is_clicked(false), is_flagged(false)
        {
            set_image("sprites/block2.bmp", "sprites/block3.bmp");
        }
        bool is_mouse_over_block(int mouse_x, int mouse_y) //checks in any block mouse is or not
        {
            if(mouse_x>x && mouse_y>y && mouse_x<x+width && mouse_y<y+height) return true;
            else return false;
        }

        static void set_width_height(int w, int h){ width=w; height=h; }

        void set_x_y(int a, int b)
        {
            menu_part::x=a; menu_part::y=b;
        }

        void display(SDL_Surface* screen, int mouse_x, int mouse_y)
        {
            SDL_Rect r;
            if(!is_clicked )
               {
                    r.x=x; r.y=y;
                   if(is_flagged) SDL_BlitSurface(flag, NULL, screen, &r);
                   else if(is_mouse_over_block(mouse_x, mouse_y))
                        menu_part::display_glow(screen);
                    else
                        menu_part::display(screen);
                    return;
               }

               r.x=x; r.y=y;
            switch (value)
            {
                case 0:{ SDL_BlitSurface(zero, NULL, screen, &r); return;}
                case 1:{ SDL_BlitSurface(one, NULL, screen, &r); return;}
                case 2:{ SDL_BlitSurface(two, NULL, screen, &r); return;}
                case 3:{ SDL_BlitSurface(three, NULL, screen, &r); return;}
                case 4:{ SDL_BlitSurface(four, NULL, screen, &r); return;}
                case 99:{ SDL_BlitSurface(mine, NULL, screen, &r); return;}
            }

        }


        ~block(){}

};
int block::width=5; int block::height=5;
SDL_Surface* block::zero= SDL_LoadBMP("sprites/zero.bmp");
SDL_Surface* block::one= SDL_LoadBMP("sprites/one.bmp");
SDL_Surface* block::two= SDL_LoadBMP("sprites/two.bmp");
SDL_Surface* block::three = SDL_LoadBMP("sprites/three.bmp");
SDL_Surface* block::four = SDL_LoadBMP("sprites/four.bmp");
SDL_Surface* block::five = SDL_LoadBMP("sprites/five.bmp");
SDL_Surface* block::flag = SDL_LoadBMP("sprites/flag.bmp");
SDL_Surface* block::mine= SDL_LoadBMP("sprites/mine.bmp");

