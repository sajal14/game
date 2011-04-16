

/*This source code copyrighted by Lazy Foo' Productions (2004-2011)
and may not be redestributed without written permission.*/

//The headers

SDL_Surface *screen = NULL;

SDL_Surface *image_quit = NULL;
SDL_Surface *image_start = NULL;

SDL_Surface *background = NULL;


SDL_Event event;
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_BPP = 32;

//Screen attributes


//The frames per second
const int FRAMES_PER_SECOND = 15;

//The dimenstions of the stick figure
const int FOO_WIDTH = 48;
const int FOO_HEIGHT = 50;

//The direction status of the stick figure
const int FOO_RIGHT = 0;
const int FOO_LEFT = 1;
const int FOO_UP = 3;
const int FOO_DOWN = 2;


//The surfaces
SDL_Surface *image = NULL;

//The event structure
//SDL_Event event;

//The areas of the sprite sheet
SDL_Rect clipsRight[ 5];
SDL_Rect clipsLeft[ 4 ];
SDL_Rect clipsUp[ 5 ];
SDL_Rect clipsDown[ 5 ];

//The stick figure
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

    public:
    //Initializes the variables
    Foo();

    //Handles input
    void handle_events();

    //Moves the stick figure
    void move();

    //Shows the stick figure
    void show();
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
};

/*SDL_Surface *load_image( std::string filename )
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
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
*/
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

/*bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Animation Test", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the sprite sheet
    image = load_image( "try.gif" );
      background = load_image( "back.png" );
    image_quit = load_image("quit.png");
    image_start = load_image("start.png");

    return true;


    //If there was a problem in loading the sprite
    if( image == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( image );

    //Quit SDL
    SDL_Quit();
}
*/
Foo::Foo()
{
    //Initialize movement variables
    xoffSet = 0;
    yoffSet = 0;
    xvelocity = 0;
    yvelocity=0;

    //Initialize animation variables
    frame = 0;
    status = FOO_RIGHT;
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

void Foo::move()
{
    //Move
    xoffSet += xvelocity;

    //Keep the stick figure in bounds
    if( ( xoffSet < 0 ) || ( xoffSet > SCREEN_WIDTH-40) )
    {
        xoffSet -= xvelocity;
    }

    yoffSet+= yvelocity;

    if((yoffSet <0)|| (yoffSet > SCREEN_HEIGHT+ FOO_HEIGHT+40))
    {

        yoffSet-= yvelocity;
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

void dino_main()
{
    //Quit flag
    bool quit = false;

    //Initialize
     if (init()== false)
     {

     }


    //Load the files
    if( load_files() == false )
    {
    }

    //Clip the sprite sheet
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
        walk.move();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0, 0xFF, 0xFF ) );

        //Show the stick figure on the screen
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

    //Clean up
//    clean_up();


}


