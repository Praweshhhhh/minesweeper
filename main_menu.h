
#include <SDL/sdl.h>
#include "menu_part.h"

class main_menu
{
  private:
        SDL_Surface *menu_screen, *background;
        SDL_Event menu_select;
        SDL_Rect background_rect;
        const int X, Y;
        int level;
        int mouse_x, mouse_y;
        menu_part m[5],sm[4];
  public:
        int selection;
        main_menu(SDL_Surface* screen):X(150),Y(0), level(1), selection(0) //puts menu and images
        {
            background_rect.x=X, background_rect.y=Y;
            menu_screen= screen;
            background= SDL_LoadBMP("sprites/background.bmp");
            m[0].set_image("sprites/new_game1.bmp", "sprites/new_game2.bmp", 30+X, 80, 140, 32);//newgame
            m[1].set_image("sprites/Selectlevel1.bmp","sprites/Selectlevel2.bmp",30+X,120,150,32);//level selection
            m[2].set_image("sprites/instructions1.bmp", "sprites/instructions2.bmp", 30+X, 160, 140, 32);//highscore
            m[3].set_image("sprites/credits1.bmp", "sprites/credits2.bmp", 30+X, 200,90, 32);//credits
            m[4].set_image("sprites/exit1.bmp", "sprites/exit2.bmp", 30+X, 240, 50, 32);//exit
            //m[4]("exit1.bmp", "exit2.bmp", 530, 400, 325, 32);//back

        }
        int selected_level()
        {
            return level;
        }
         void on_clicking(int i) //puts respective imges or sub menu on clicking
        {
            if (i==0) { selection=1; mouse_x=4000; mouse_y=3000;}
            if (i==1) select_level(); //select level
            if (i==2)  high_credits("sprites/instructions.bmp");//instructions
            if (i==3)  high_credits("sprites/names.bmp");//credits
            if (i==4)  {selection=4; level=0;}//infinite loop of main_menu class terminates and program exits
        }
        void select_level() //menu that appears after clicking on select level
        {
            int b=0;
            static int selected =9;
            sm[0].set_image("sprites/beginner1.bmp","sprites/beginner2.bmp",180+X,150,140,32);
            sm[1].set_image("sprites/medium1.bmp","sprites/medium2.bmp",180+X,200,90,32);
            sm[2].set_image("sprites/hard1.bmp","sprites/hard2.bmp",180+X,250,50,32);
            sm[3].set_image("sprites/back1.bmp","sprites/back2.bmp",500+X,400,40,32);
            for(int i=0; i<4; i++)
              sm[i].colour_udaune(255, 255, 255);

            while (!b )
               {

                   SDL_BlitSurface(background, NULL, menu_screen, &background_rect);
                    SDL_PollEvent(&menu_select);
                    if (menu_select.type == SDL_MOUSEMOTION)
                    {
                        mouse_x=menu_select.motion.x; mouse_y=menu_select.motion.y;
                    }

                    for(int i=0; i<4; i++)
                    {
                        if( sm[i].is_mouse_over(mouse_x, mouse_y))
                              sm[i].display_glow(menu_screen);
                        else if(i==selected)
                            sm[i].display_glow(menu_screen);
                        else
                          sm[i].display(menu_screen);
                    }
                    SDL_Flip(menu_screen);

                    for(int j=0; j<4; j++)
                    if(sm[j].is_mouse_over(mouse_x, mouse_y) &&menu_select.type == SDL_MOUSEBUTTONDOWN  && menu_select.button.button == SDL_BUTTON_LEFT )
                    { if(j==3)
                          { b=1; selection=0; }
                      else
                      {
                          selected=j;
                          level=j+1;
                      }
                    }
               }
        }
        void high_credits(char* s)  //runs when credits is clicked
        {
            int b=0;
                menu_part back;
                SDL_Event back_click;
                back.set_image("sprites/back1.bmp", "sprites/back2.bmp", 630, 500, 325, 32);
                back.colour_udaune(255, 255, 255);
                SDL_Surface* score_credits= SDL_LoadBMP(s);
                SDL_SetColorKey(score_credits, SDL_SRCCOLORKEY ,SDL_MapRGB (score_credits->format ,255,255,255) );
                SDL_Rect rect;
                rect.x=X; rect.y=0;
                SDL_BlitSurface(background, NULL, menu_screen, &background_rect);
                SDL_BlitSurface(score_credits, NULL, menu_screen, &rect);
                while(!b)
                 {
                     //SDL_BlitSurface(background, NULL, menu_screen, NULL);
                    //SDL_BlitSurface(score_credits, NULL, menu_screen, &rect);
                    SDL_PollEvent(&back_click);
                    if (back_click.type == SDL_MOUSEMOTION)
                    {
                        mouse_x=back_click.motion.x; mouse_y=back_click.motion.y;
                    }

                    if(back.is_mouse_over(mouse_x, mouse_y))
                        back.display_glow(menu_screen);
                    else
                        back.display(menu_screen);

                    SDL_Flip(menu_screen);

                    if(back.is_mouse_over(mouse_x, mouse_y) && back_click.type == SDL_MOUSEBUTTONUP  && back_click.button.button == SDL_BUTTON_LEFT )
                    { b=1; selection=0;}
                 }
        }

        void show()
        {
            selection=0;
            for(int i=0; i<5; i++)
              m[i].colour_udaune(255, 255, 255);

            while (selection==0 )
               {

                   SDL_BlitSurface(background, NULL, menu_screen, &background_rect);
                    SDL_PollEvent(&menu_select);
                    if (menu_select.type == SDL_MOUSEMOTION )//|| menu_select.type== SDL_MOUSEBUTTONDOWN|| menu_select.type== SDL_MOUSEBUTTONUP)
                    {
                            mouse_x=menu_select.motion.x; mouse_y=menu_select.motion.y;
                    }
                    //else { mouse_x=5000; mouse_y=8000;}

                        for(int i=0; i<5; i++)
                        {
                            if( m[i].is_mouse_over(mouse_x, mouse_y))
                                  m[i].display_glow(menu_screen);
                            else
                              m[i].display(menu_screen);
                        }
                        SDL_Flip(menu_screen);

                        for(int j=0; j<5; j++)
                        if(m[j].is_mouse_over(mouse_x, mouse_y) &&menu_select.type == SDL_MOUSEBUTTONDOWN  && menu_select.button.button == SDL_BUTTON_LEFT )
                        { on_clicking(j); }

               }
        }

};
