#include<iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <sstream>
#include <string>
#include<time.h>
#include "SDL/SDL_mixer.h"
//#include "add_dino.cpp"

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
Uint32 start = 0;
Uint32 t = 0;


Mix_Chunk *collide = NULL;
Mix_Chunk *button = NULL;
Mix_Chunk *times_up = NULL;
Mix_Chunk *fire_end = NULL;





SDL_Surface *background = NULL;
SDL_Surface *fire_back=NULL;
SDL_Surface *image_quit = NULL;
SDL_Surface *image_start = NULL;
SDL_Surface *back_grass = NULL;

SDL_Surface *image = NULL;
SDL_Surface *fire_img = NULL;

SDL_Surface *screen = NULL;
SDL_Surface *fruit1= NULL;


SDL_Surface *score_dis = NULL;
SDL_Surface *score_no = NULL;


SDL_Surface *seconds = NULL;
TTF_Font *font = NULL;

SDL_Surface *mesg = NULL;

SDL_Color textColor = { 10, 10, 255 };

SDL_Rect wall;
SDL_Rect wall2;
SDL_Rect msg;

const int FRAMES_PER_SECOND = 10;

const int FOO_WIDTH = 48;
const int FOO_HEIGHT = 50;

//The direction status of the stick figure
const int FOO_RIGHT = 0;
const int FOO_LEFT = 1;
const int FOO_UP = 3;
const int FOO_DOWN = 2;

void dino_main();

//SDL_Surface *up = NULL;
//SDL_Surface *down = NULL;
//SDL_Surface *screen = NULL;


SDL_Event event;

SDL_Rect clipsRight[ 5 ];
SDL_Rect clipsLeft[ 4 ];
SDL_Rect clipsUp[ 5 ];
SDL_Rect clipsDown[ 5 ];

//int i,randx[600],randy[400];




//for(i=0;i<600;i++)
//{
// int randx[i]= rand()%600 + 1;

//}
//for(i=0;i<420;i++)
//{
  //   int randy[i]= rand()%420 + 1;

//}


int randx[600],randy[420];

class Foo
{
    private:
    //The offset
    int xoffSet;
    int yoffSet;

    //Its rate of movement
    int xvelocity;
    int yvelocity;

    //Its current frame
    int frame;

    //Its animation status
    int status;


    int inpos,xpos,ypos;

    int score;

    int fire;

  //  int randx[600],randy[400];



    public:
    //Initializes the variables
    Foo();

    //Handles input
    void handle_events();

    //Moves the stick figure
    void move(int a[],int b[]);

    //Shows the stick figure
    void show();


    //int object_check(int,int,int,int);
};

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
} t1;

class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;

    public:
    //Initialize the variables
    Button( int x, int y, int w, int h );

    //Handles events and set the button's sprite region
    void handle_events(int);

    //Shows the button on the screen
    void show(int);
};

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination,SDL_Rect* clip=NULL)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source,clip, destination, &offset );
}

void set_clips()
{
    //Clip the sprites
    clipsRight[ 0 ].x = 0;
    clipsRight[ 0 ].y = 0;
    clipsRight[ 0 ].w = 40;
    clipsRight[ 0 ].h = 50;

    clipsRight[ 1 ].x = 40;
    clipsRight[ 1 ].y = 0;
    clipsRight[ 1 ].w = 50;
    clipsRight[ 1 ].h = 50;

    clipsRight[ 2 ].x = 90;
    clipsRight[ 2 ].y = 0;
    clipsRight[ 2 ].w = 50;
    clipsRight[ 2 ].h = 50;

    clipsRight[ 3 ].x = 140;
    clipsRight[ 3 ].y = 0;
    clipsRight[ 3 ].w = 50;
    clipsRight[ 3 ].h = 50;

      clipsRight[ 4 ].x = 190;
    clipsRight[ 4 ].y = 0;
    clipsRight[ 4 ].w = 45;
    clipsRight[ 4 ].h = 50;

    clipsLeft[ 0 ].x = 270;
    clipsLeft[ 0 ].y = 220;
    clipsLeft[ 0 ].w =40;
    clipsLeft[ 0 ].h =40;

    clipsLeft[ 1 ].x = 310;
    clipsLeft[ 1 ].y = 220;
    clipsLeft[ 1 ].w = 40;
    clipsLeft[ 1 ].h = 40;

    clipsLeft[ 2 ].x = 350;
    clipsLeft[ 2 ].y = 220;
    clipsLeft[ 2 ].w = 45;
    clipsLeft[ 2 ].h = 40;

    clipsLeft[ 3 ].x = 395;
    clipsLeft[ 3 ].y = 220;
    clipsLeft[ 3 ].w = 40;
    clipsLeft[ 3 ].h = 40;




    clipsUp[ 0 ].x = 0;
    clipsUp [ 0 ].y = 100;
    clipsUp[ 0 ].w = 50;
    clipsUp[ 0 ].h = 50;

    clipsUp[ 1 ].x = 50;
    clipsUp[ 1 ].y = 100;
    clipsUp[ 1 ].w = 50;
    clipsUp[ 1 ].h = 50;

    clipsUp[ 2 ].x = 100;
    clipsUp[ 2 ].y = 100;
    clipsUp[ 2 ].w = 40;
    clipsUp[ 2 ].h = 50;

    clipsUp[ 3 ].x = 140;
    clipsUp[ 3 ].y = 100;
    clipsUp[ 3 ].w = 45;
    clipsUp[ 3 ].h = 50;

    clipsUp[ 4].x = 185;
    clipsUp[ 4 ].y = 100;
    clipsUp[ 4 ].w = 45;
    clipsUp[ 4 ].h = 50;



 clipsDown[ 0 ].x = 0;
    clipsDown [ 0 ].y = 50;
   clipsDown[ 0 ].w = 40;
   clipsDown[ 0 ].h = 50;

    clipsDown[ 1 ].x = 40;
    clipsDown[ 1 ].y = 50;
   clipsDown[ 1 ].w = 45;
    clipsDown[ 1 ].h = 50;

    clipsDown[ 2 ].x = 85;
    clipsDown[ 2 ].y = 50;
    clipsDown[ 2 ].w = 50;
    clipsDown[ 2 ].h = 50;

    clipsDown[ 3 ].x = 135;
    clipsDown[ 3 ].y = 50;
    clipsDown[ 3 ].w = 50;
    clipsDown[ 3 ].h = 50;

    clipsDown[ 4].x = 185;
    clipsDown[ 4 ].y = 50;
    clipsDown[ 4 ].w = 45;
    clipsDown[ 4 ].h = 50;
}


bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    if( TTF_Init() == -1 )
    {
        return false;
    }

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }


    //Set the window caption
    SDL_WM_SetCaption( "WELCOME TO SHOOTER v3.8", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the button sprite sheet
    background = load_image( "back.png" );
    image_quit = load_image("quit.png");
    image_start = load_image("start.png");
    image = load_image( "try.gif" );
    back_grass = load_image("Untitled.png");
    fruit1 = load_image("banana.png");
    fire_img = load_image("fire.jpg");
    fire_back= load_image("fire_back.jpg");

    font = TTF_OpenFont( "stencil0.ttf", 28 );
    collide = Mix_LoadWAV( "LaserGun.wav" );
    button= Mix_LoadWAV("button.wav");
    times_up=Mix_LoadWAV("time.wav");
    fire_end=Mix_LoadWAV("fire.wav");
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface(background );
    SDL_FreeSurface(image_quit);
    SDL_FreeSurface(image_start);
    SDL_FreeSurface( image );
    SDL_FreeSurface(back_grass);
    SDL_FreeSurface(fruit1);
    SDL_FreeSurface(fire_img);
        SDL_FreeSurface(fire_back);



    Mix_FreeChunk( collide );
    Mix_FreeChunk( button );
        Mix_FreeChunk( times_up );
                Mix_FreeChunk( fire_end );

    //SDL_FreeSurface(up);
    //SDL_FreeSurface( down);

    //Quit SDL
    TTF_CloseFont( font );

    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();
    SDL_Quit();
}



Foo::Foo()
{
    //Initialize movement variables
    xoffSet = 0;
    yoffSet = 0;
    xvelocity = 0;
    yvelocity=0;

    inpos = 0;
    score=0;
    fire=0;

    xpos= randx[0];
    ypos=randy[0];
    //Initialize animation variables
    frame = 0;
    status = FOO_RIGHT;


//for(int i=0;i<600;i++)
//{
//  randx[0]= rand()%600 + 1;

//}

  //  for(int i=0;i<600;i++)
//{
// randy[0]= rand()%420 + 1;

//}


}

void Foo::handle_events()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: xvelocity += FOO_WIDTH /4; break;
            case SDLK_LEFT: xvelocity -= FOO_WIDTH / 4; break;
            case SDLK_DOWN: yvelocity += FOO_WIDTH / 4; break;
            case SDLK_UP: yvelocity -= FOO_WIDTH / 4; break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Set the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_RIGHT: xvelocity -= FOO_WIDTH / 4; break;
            case SDLK_LEFT: xvelocity += FOO_WIDTH / 4; break;
            case SDLK_DOWN: yvelocity -= FOO_WIDTH / 4; break;
            case SDLK_UP: yvelocity += FOO_WIDTH / 4; break;
        }
    }
}


bool check_collision( int x,int y, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
   leftA = x;
    rightA = x + 40;
    topA = y;
    bottomA = y + 40;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


bool object_check(int x1, int y1,int x2,int y2)
{  int leftA,rightA, topA,bottomA;
    int leftB,rightB,topB,bottomB;


    leftA=x1;
    topA=y1;
    rightA=x1+40;
    bottomA=y1+50;

    leftB=x2;
    topB=y2;
    rightB=x2+40;
    bottomB=y2+50;



  if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return 1;
}




void Foo::move(int randx[],int randy[])
{



       //Move
    xoffSet += xvelocity;

        yoffSet+= yvelocity;


    //Keep the stick figure in bounds
    if (score >= 5)
{
    if(( check_collision( xoffSet,yoffSet, wall ) )|| (check_collision(xoffSet,yoffSet,wall2)))
    {
        fire =1;

         }

}
    if(( xoffSet < 0 ) || ( xoffSet > SCREEN_WIDTH-40)||( check_collision( xoffSet,yoffSet, wall ) )|| (check_collision(xoffSet,yoffSet,wall2)))
    {
        xoffSet -= xvelocity;

    }




    if((yoffSet <0)|| (yoffSet > SCREEN_HEIGHT-FOO_HEIGHT-20)||( check_collision( xoffSet,yoffSet, wall ) )|| (check_collision(xoffSet,yoffSet,wall2)))
    {

        yoffSet-= yvelocity;

    }






    if(object_check(xoffSet,yoffSet,xpos,ypos))
   {
   // xoffSet -= xvelocity;
    score = score+5;

    inpos=inpos+1;

    Mix_PlayChannel( -1, collide, 0 );
    /*if (inpos==1)
    {
       t1.start();

    }*/
    t+=4-((SDL_GetTicks() - start)/1000);
    start=SDL_GetTicks();
    //final= 10-((SDL_GetTicks() - start)/1000) + t;

   }




}



void Foo::show()
{
    //If Foo is moving left
    if( xvelocity < 0 )
    {
        //Set the animation to left
        status = FOO_LEFT;

        //Move to the next frame in the animation
        frame++;
    }
    //If Foo is moving right
    else if( xvelocity > 0 )
    {
        //Set the animation to right
        status = FOO_RIGHT;

        //Move to the next frame in the animation
        frame++;
    }



    else if( yvelocity < 0 )
    {
        //Set the animation to right
        status = FOO_UP;

        //Move to the next frame in the animation
        frame++;
    }


    else if( yvelocity > 0 )
    {
        //Set the animation to right
        status = FOO_DOWN;

        //Move to the next frame in the animation
        frame++;
    }
    //If Foo standing
    else
    {
        //Restart the animation
        frame = 0;
    }

    //Loop the animation
    if( frame >= 4 )
    {
        frame = 0;
    }

    //Show the stick figure
    if( status == FOO_RIGHT )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsRight[frame] );
    }

    else if( status == FOO_LEFT )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsLeft[frame] );
    }

   else if( status == FOO_UP )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsUp[ frame ] );
    }

     else if( status == FOO_DOWN )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsDown[ frame ] );
    }





xpos= randx[inpos];
ypos= randy[inpos];

char score_str[5];

apply_surface(xpos,ypos,fruit1,screen);

itoa(score,score_str,10);

score_no = TTF_RenderText_Solid( font, score_str, textColor );
apply_surface( 580, 450, score_no, screen );


//start= SDL_GetTicks();
std::stringstream time;

            //Convert the timer's time to a string
            time << "Timer: " <<  10-((SDL_GetTicks() - start)/1000) + t;
            /*if( (((10-SDL_GetTicks() - start)/1000))==0)
            {
               SDL_Quit();
               //apply_surface(2,2,fruit1,screen);
                }*/

            if (score>=5)
            {

                apply_surface(0,220,fire_img,screen);

                apply_surface(360,220,fire_img,screen);
            }
            //Render the time surface
            seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );

            //Apply the time surface
            if(((10-((SDL_GetTicks() - start)/1000))+t)!=0)
            apply_surface( 100, 450, seconds, screen );
            else
            {
                //SDL_FillRect( screen, &msg, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ) );
                /*mesg = TTF_RenderText_Solid( font, "GAME OVER!", textColor );
                apply_surface( 280, 240, mesg, screen );
                SDL_Delay(5000);*/
                Mix_PlayChannel( -1, times_up, 0 );

                apply_surface(0,0,back_grass,screen);
                mesg = TTF_RenderText_Solid( font, "!OOPS! TIMES UP GAME OVER!", textColor );
                apply_surface(150,200,mesg,screen);
                apply_surface(280,240,score_dis,screen);
                //score_no = TTF_RenderText_Solid( font, score_str, textColor );
                apply_surface(400,240,score_no,screen);

                /*Button button_equit( 239, 380,160 , 50);
                button_equit.show(2);
                if( SDL_PollEvent( &event ) )
                button_equit.handle_events(2);*/


                SDL_Flip( screen );
                SDL_Delay(5000);
                clean_up();
                SDL_Quit();

            }

        if (fire==1)
        {
             apply_surface(0,0,fire_back,screen);
                mesg = TTF_RenderText_Solid( font, "AH!! THAT SHOULD HAVE BURNT.", textColor );
                                Mix_PlayChannel( -1, fire_end, 0 );

                apply_surface(50,200,mesg,screen);
                apply_surface(280,240,score_dis,screen);
                apply_surface(400,240,score_no,screen);

                                SDL_Flip( screen );

                SDL_Delay(5000);
                clean_up();
                SDL_Quit();
        }


  /* if(inpos==1)
    {

        //apply_surface(300,400,fruit1,screen);
        //SDL_FreeSurface(fruit1);
        int x,y;
        xpos= randx[20];
        ypos= randy[10];

        apply_surface(0,0,back_grass,screen);

        SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ) );  //set walls

        SDL_FillRect( screen, &wall2, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ));
        //this->show();
        //this->move();

    if( status == FOO_RIGHT )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsRight[frame] );
    }

    else if( status == FOO_LEFT )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsLeft[frame] );
    }

   else if( status == FOO_UP )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsUp[ frame ] );
    }

     else if( status == FOO_DOWN )
    {
        apply_surface( xoffSet, yoffSet, image, screen, &clipsDown[ frame ] );
    }


   apply_surface(xpos,ypos,fruit1,screen);

    }
*/

}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}


Button::Button( int x, int y, int w, int h )
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    //Set the default sprite
 //   clip = &clips[ CLIP_MOUSEOUT ];
}
void Button::handle_events(int flag)
{
    //The mouse offsets
    int x = 0, y = 0;
    bool quit= false;

    //If the mouse moved

    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;


            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                if (flag==0||flag==2)
                    {
                        Mix_PlayChannel( -1, button, 0 );
                        SDL_Delay(500);
                            SDL_Quit() ;
                    }

                else if(flag==1)
                    {
                    Mix_PlayChannel( -1, button, 0 );
                     SDL_Delay(500);
                    dino_main();
                    }

            }
        }
    }


    //If a mouse button was released
    /*if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Set the button sprite

            }
        }
    }*/
}


void Button::show(int flag)
{
    //Show the button
    if(flag==0)
    apply_surface( box.x, box.y, image_quit, screen);
    else if(flag==1)
        apply_surface( box.x, box.y, image_start, screen);
        else if(flag==2)
        apply_surface( box.x, box.y, image_quit, screen);


   // apply surface(box.x, boy.y,button_s,screen)
}







void dino_main()
{
start= SDL_GetTicks();


for(int i=0;i<600;i++)
{
  randx[i]= rand()%600 + 1;
  randy[i]= rand()%420 + 1;

  if (randy[i]>220 && randy[i]<270)
  {
      randx[i]=randx[i-1];
      randy[i]=randx[i-1];

  }
}


    bool quit = false;
    set_clips();

    //The frame rate regulator
    Timer fps;


    //The stick figure
    Foo walk;


    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();


        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the stick figure
            walk.handle_events();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Move the stick figure
        walk.move(randx,randy);

        //Fill the screen white
        //SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ) );
            apply_surface(0,0,back_grass,screen);
             score_dis = TTF_RenderText_Solid( font, "Score", textColor );

                apply_surface( 460, 450, score_dis, screen );



SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ) );

        SDL_FillRect( screen, &wall2, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ));



         walk.show();
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {

        }

        //Cap the frame rate
       if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
       {
           SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

}



int main( int argc, char* args[] )
{
    int flag=0;

    //Quit flag
    bool quit = false;

    wall.x = 360;
    wall.y = 220;
    wall.w = 640;
    wall.h = 50;


    wall2.x = 0;
    wall2.y = 220;
    wall2.w = 280;
    wall2.h = 50;

    msg.x = 0;
    msg.y = 60;
    msg.w = 640;
    msg.h = 420;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    apply_surface(0,0,background,screen);



    //Clip the sprite sheet


    //Make the button
    Button button_quit( 239, 380,160 , 50);
    button_quit.show(flag);
    flag=1;
    Button button_start(239 , 240 ,160,50);
    button_start.show(flag);
//    Button button_quit( 239, 380,160 , 50);
  //  button_quit.show(2);



    //While the user hasn't quit
    while( quit == false )
    {
        //If there's events to handle
        if( SDL_PollEvent( &event ) )
        {
            //Handle button events
            flag=0;
            button_quit.handle_events(flag);

            flag=1;
            button_start.handle_events(flag);

            flag=2;
            button_quit.handle_events(flag);


            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
       }
    }

    //Clean up
    clean_up();

    return 0;
}


