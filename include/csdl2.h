#ifndef SDL2_H
#define SDL2_H

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "cgl.h"
class CSDL2
{
    public:
        CSDL2();
        CSDL2(int width, int height, CGL* gl);
        ~CSDL2();
        void quit(int code);
        void toggleFullscreen();
        void handleKeyEvent( SDL_Keysym* keysym ,CGL* gl);
        void handleEvents(CGL* gl);
        void sdldie(const char *msg);
        void checkSDLError(int line = -1);
    protected:
    private:
        int screen_width;
        int screen_height;
        SDL_Window *mainwindow;
        SDL_GLContext maincontext;
        //Whether the window is windowed or not
        bool windowed;
        //Whether the window is fine
        bool windowOK;
};

#endif
