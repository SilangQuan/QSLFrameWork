#include "csdl2.h"

CSDL2::CSDL2()
{
    //ctor

}
CSDL2::CSDL2(int width, int height, CGL* gl)
{
    screen_height = height;
    screen_width = width;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */

    /* Request opengl 3.2 context.
         * SDL doesn't have the ability to choose which profile at this time of writing,
         * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    /* Turn on double buffering with a 24bit Z buffer.
         * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow("OpenGL in SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  screen_width, screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if (!mainwindow) /* Die if creation failed */
    {
        sdldie("Unable to create window");
    }
    else windowed=true;

    checkSDLError(__LINE__);

    maincontext = SDL_GL_CreateContext(mainwindow);
    gl->resizeGL(screen_width, screen_height);
    if(glewInit() != GLEW_OK) exit(EXIT_FAILURE);
    else cout<<"GLEW init successful!"<<endl;

    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);
}

CSDL2::~CSDL2()
{
    //dtor
}


void CSDL2::quit(int code)
{
    SDL_Quit();
    exit(code);
}

void CSDL2::sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void CSDL2::handleEvents(CGL* gl)
{
    // Our SDL event placeholder.
    SDL_Event event;
    //Grab all the events off the queue.
    while( SDL_PollEvent( &event ) ) {
        switch( event.type ) {
        case SDL_KEYDOWN:
            // Handle key Event
            handleKeyEvent( &event.key.keysym, gl);
            break;
        case SDL_QUIT:
            // Handle quit requests (like Ctrl-c).
            quit( 0 );
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                if ( mainwindow )
                {
                    int tmpX,tmpY;
                    SDL_GetWindowSize(mainwindow,&tmpX,&tmpY);
                    gl->resizeGL(tmpX, tmpY);

                }
            }
            SDL_GL_SwapWindow(mainwindow);
            break;
        }
    }
}

void CSDL2::handleKeyEvent( SDL_Keysym* keysym ,CGL* gl)
{
    switch( keysym->sym )
    {
    case SDLK_ESCAPE:
        this->quit( 0 );
        break;
    case SDLK_SPACE:
        break;
    case SDLK_F1:
        this->toggleFullscreen();
        break;
    case SDLK_r:
        //gl->changeMatrics();
        gl->changeMatrics();
        cout<<"Fuck"<<endl;
        break;

    default:
        break;
    }
}

void CSDL2::toggleFullscreen()
{
    //If the screen is windowed
    if( windowed == true )
    {
        //Set the screen to fullscreen
        int result = SDL_SetWindowFullscreen( mainwindow, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN );

        //If there's an error
        if( result < 0 )
        {
            windowOK = false;
            return;
        }
        //Set the window state flag
        windowed = false;
    }
    //If the screen is fullscreen
    else if( windowed == false )
    {
        //Window the screen
        SDL_SetWindowSize(mainwindow, screen_width, screen_height);
        //Set the window state flag
        windowed = true;
    }
}

void CSDL2::checkSDLError(int line)
{
#ifndef NDEBUG
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
    }
#endif
}
