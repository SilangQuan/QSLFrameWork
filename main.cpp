#include <iostream>
#include "csdl2.h"
#include "cgl.h"
using namespace std;

const int SCREEN_WIDTH = 800;  
const int SCREEN_HEIGHT =600; 
SDL_Window *mainwindow; /* Our window handle */

/* Our program's entry point */
int main(int argc, char *argv[])
{
    CGL *gl = new CGL(SCREEN_WIDTH, SCREEN_HEIGHT, mainwindow);

    CSDL2 *sdl = new CSDL2(SCREEN_WIDTH, SCREEN_HEIGHT, gl);
    gl->initGL();


    gl->compileShader();
    //gl->loadTexture();
    gl->setUniform();


    while(true)
    {
        /* Process incoming events. */
        sdl->handleEvents(gl);
        /*Render scene*/
        gl->renderGL();
    }

    gl->clean();
    return 0;
}
