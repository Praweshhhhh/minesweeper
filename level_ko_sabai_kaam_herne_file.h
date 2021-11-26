

#include<SDL/sdl.h>
#include "block.h"
#include <iostream>
#include <fstream>
    using namespace std;

class level
{
    private:
        char ch[25][25];
        int displayed[25][25];
        int select_level;
        int mouse_x, mouse_y;
        int no_of_rows, no_of_columns;
        int total_no_of_mines, clicked_blocks, no_of_flags, no_of_mines_in_level, no_of_displayed_blocks;

        SDL_Surface *img;
        SDL_Surface *surface;
        SDL_Rect rect1;

        void check_zeroes(int row, int col);
        void main_level_function();
        void load_level_from_file();
        void reset_level();
        void inform_the_loser();
        void inform_the_winner();
        void dammi_display();
        int check_mine(char c);
        int X_POSITION, Y_POSITION;
        void level1();
        void level2();
        void level3();
        block b[25][25];


    public:
        bool lost, won;
        level(SDL_Surface* screen):X_POSITION(0), Y_POSITION(0), surface(screen), mouse_x(0), mouse_y(0), lost(false),won(false), no_of_displayed_blocks(0)
        {
            total_no_of_mines=0;
             no_of_flags=0;
            clicked_blocks=0;
            for(int i=0; i<25; i++)
            {
                for(int j=0; j<25; j++)
                { ch[i][j]='\0'; displayed[i][j]=0; }
            }
        }

        void show_level( int i)
        {
            select_level=i;
            if(i==1) level1();
            if(i==2) level2();
            if(i==3) level3();
        }
    //SDL_Delay(10000);
};


int level::check_mine(char c)
{
    if(c=='m') return 1; return 0;
}

void level::load_level_from_file()
{
    int x=0, y=0, k=0; char c, dummyc, check[360];
    ifstream infile;
    if(select_level==1) infile.open("level1.txt");
    if(select_level==2) infile.open("level2.txt");
    if(select_level==3) infile.open("level3.txt");

              static int kun_chai_level=1;
              kun_chai_level=rand()%4;
            for(int j=0; j<kun_chai_level; j++)
                {
                     while(check[k-1] != '\n')
                    {
                        infile.get(check[k++]);
                    }
                    k=0;
                }

        while(dummyc!='e')
        {
            infile>>x>>c>>y>>dummyc;
            ch[x][y]= 'm';
        }

    for(int i=0; i<no_of_rows; i++)
    {
        for(int j=0; j<no_of_columns; j++)
        {
            if(check_mine( ch[i][j] )==1){ b[i][j].value=99; total_no_of_mines++;}
            else
                {
                     if(i-1>=0         && j-1>=0           ) b[i][j].value += check_mine(ch[i-1][j-1]);
                     if(                  j-1>=0           ) b[i][j].value += check_mine(ch[i][j-1]);
                     if(i+1<no_of_rows && j-1>=0           ) b[i][j].value += check_mine(ch[i+1][j-1]);
                     if(i+1<no_of_rows                     ) b[i][j].value += check_mine(ch[i+1][j]);
                     if(i+1<no_of_rows && j+1<no_of_columns) b[i][j].value += check_mine(ch[i+1][j+1]);
                     if(                  j+1<no_of_columns) b[i][j].value += check_mine(ch[i][j+1]);
                     if(i-1>=0         && j+1<no_of_columns) b[i][j].value += check_mine(ch[i-1][j+1]);
                     if(i-1>=0                             ) b[i][j].value += check_mine(ch[i-1][j]);
                }
        }
    }

}

void level::main_level_function()
{
        lost= false;
        won=false;
        SDL_Event mouse_event;
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0) ); //SDL_Delay(1000);

      for(int i=0;i<no_of_rows;i++)
      {
        for(int j=0;j<no_of_columns;j++)
        {
            b[i][j].set_x_y(X_POSITION+ i*block::width, Y_POSITION+ j*block::height);
        }
      }

        dammi_display();
      while(!lost && !won)
      {
          SDL_PollEvent(&mouse_event);
          if(mouse_event.type==SDL_KEYDOWN && mouse_event.key.keysym.sym== SDLK_ESCAPE){ reset_level(); break; }
          if(mouse_event.type==SDL_MOUSEMOTION) { mouse_x= mouse_event.motion.x; mouse_y= mouse_event.motion.y; }
                if(mouse_event.type==SDL_MOUSEBUTTONDOWN || SDL_MOUSEBUTTONUP)
                {

                        for(int i=0;i<no_of_rows;i++)
                      {
                        for(int j=0;j<no_of_columns;j++)
                        {
                            if( b[i][j].is_mouse_over_block(mouse_x, mouse_y) && b[i][j].is_clicked==false )
                            {
                                if(mouse_event.type==SDL_MOUSEBUTTONDOWN && mouse_event.button.button==SDL_BUTTON_LEFT)
                                {
                                      b[i][j].is_clicked=true;
                                      check_zeroes(i,j);
                                      if( b[i][j].value==99 )
                                       { lost=true; break; }
                                }

                                if(mouse_event.type== SDL_MOUSEBUTTONUP && mouse_event.button.button==SDL_BUTTON_RIGHT)
                                {
                                    if(b[i][j].is_flagged==false)
                                        b[i][j].is_flagged=true;
                                    else if(b[i][j].is_flagged==1)
                                        b[i][j].is_flagged=false;
                                        mouse_x=7000; mouse_y=7000;
                                }

                             }//end of if statement
                        }
                    }//end of the for loops
                }//end of the main if statement of mouse_click event
                //SDL_Delay(2000);
                if( ( no_of_rows*no_of_columns)-clicked_blocks == total_no_of_mines  ) {  won=true; }
                clicked_blocks=0;
                for(int row=0;row<no_of_rows;row++)
                  {
                    for(int col=0;col<no_of_columns;col++)
                    {
                        if( b[row][col].is_clicked ==1) clicked_blocks++;
                        b[row][col].display(surface, mouse_x, mouse_y);
                    }
                  }

            if(lost){ SDL_Delay(1500); reset_level(); inform_the_loser(); SDL_Flip(surface); SDL_Delay(2000); }
            if(won) { SDL_Delay(1500); reset_level(); inform_the_winner(); SDL_Flip(surface); SDL_Delay(2000); }
            SDL_Flip(surface);

        }//end of while loop

}//end of main_level_function
void level::level1()
{
    block::set_width_height(35,35);
    no_of_rows=9;
    no_of_columns=9;
    X_POSITION = (1366/2)-(no_of_columns*block::width)/2;
    Y_POSITION = (768/2)-(no_of_rows* block::height)/2;
    load_level_from_file();
    main_level_function();
}
void level::level2()
{
    block::set_width_height(35,35);
    no_of_rows=16;
    no_of_columns=16;
    X_POSITION = (1366/2)-(no_of_columns*block::width)/2;
    Y_POSITION = (768/2)-(no_of_rows* block::height)/2;
    load_level_from_file();
    main_level_function();
}
void level::level3()
{
    block::set_width_height(35,35);
    no_of_rows=20;
    no_of_columns=20;
    X_POSITION = (1366/2)-(int)( (no_of_columns*block::width)/2 );
    Y_POSITION = (768/2)-(int)( (no_of_rows* block::height)/2 );
    load_level_from_file();
    main_level_function();
}

void level::check_zeroes(int row, int col)
{
    b[row][col].is_clicked=1;
    if(b[row][col].value!=0) return;

    if( row-1>=0 &&         col-1>=0             && b[row-1][col-1].is_clicked==0) check_zeroes(row-1, col-1);
    if(                     col-1>=0             && b[row][col-1].is_clicked==0)   check_zeroes(row, col-1);
    if( row+1<no_of_rows && col-1>=0             && b[row+1][col-1].is_clicked==0) check_zeroes(row+1, col-1);
    if( row+1<no_of_rows                         && b[row+1][col].is_clicked==0) check_zeroes(row+1, col);
    if( row+1<no_of_rows && col+1<no_of_columns  && b[row+1][col].is_clicked==0) check_zeroes(row+1, col+1);
    if(                     col+1<no_of_columns  && b[row][col+1].is_clicked==0) check_zeroes(row, col+1);
    if( row-1>=0 &&         col+1<no_of_columns  && b[row-1][col+1].is_clicked==0) check_zeroes(row-1, col+1);
    if( row-1>=0                                 && b[row-1][col].is_clicked==0 )  check_zeroes(row-1, col);
}

void level::reset_level()
{
    clicked_blocks=0;
    total_no_of_mines=0;
    no_of_displayed_blocks=0;
    for(int i=0; i<no_of_rows; i++)
      {
          for(int j=0; j<no_of_columns; j++)
            {
                b[i][j].is_clicked=0;
                b[i][j].value=0;
                b[i][j].is_flagged=0;
                ch[i][j]='\0';
                displayed[i][j]=0;
            }
      }
}

void level::inform_the_loser()
{
    SDL_Rect message; message.x=150; message.y=0;
    SDL_Surface* you_lose = SDL_LoadBMP("sprites/you_lose.bmp");
    SDL_BlitSurface(you_lose, NULL, surface, &message);
}

void level::inform_the_winner()
{
     SDL_Rect message; message.x=150; message.y=0;
    SDL_Surface* you_win = SDL_LoadBMP("sprites/you_win.bmp");
    SDL_BlitSurface(you_win, NULL, surface, &message);
}

void level::dammi_display()
{
    int which_to_display=rand()%3;
        if(which_to_display==0)
        {
        while(no_of_displayed_blocks< no_of_columns*no_of_rows)
          {
              int row_to_be_displayed=(rand())%no_of_rows;
              int column_to_be_displayed=rand()%no_of_columns;
              if(displayed[row_to_be_displayed][column_to_be_displayed]==0)
              {
                    displayed[row_to_be_displayed][column_to_be_displayed]=1; no_of_displayed_blocks++;
                    b[row_to_be_displayed][column_to_be_displayed].display(surface, mouse_x, mouse_y);
                    SDL_Flip(surface);
                    //SDL_Delay(5);
              }


          }
          return;
        }
        else if(which_to_display==1)
          {
                  for(int row=0;row<no_of_rows;row++)
                  {
                    for(int col=0;col<no_of_columns;col++)
                    {
                        b[row][col].display(surface, mouse_x, mouse_y);
                        SDL_Flip(surface);
                    }
                  }
                  return;
          }
          else if(which_to_display==2)
          {
              for(int col=0;col<no_of_columns;col++)
                  {
                    for(int row=0;row<no_of_rows;row++)
                    {
                        b[row][col].display(surface, mouse_x, mouse_y);
                        SDL_Flip(surface);
                    }
                  }
                  return;
          }
}
