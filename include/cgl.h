#ifndef CGL_H
#define CGL_H

#include <SDL2/SDL.h>
#include "util.h"
#include "shaderprogram.h"
#include "cassimpmodel.h"
class CGL
{
    public:
        CGL();
        CGL(int _width, int _height, SDL_Window *w);
         ~CGL();
        bool initGL();
        void compileShader();
        bool resizeGL(int width,int height);
        bool renderGL();
        void setUniform();
        void clean();
        void changeMatrics();
        bool fileExists( const string & fileName );


    private:
        int width;
        int height;
        mat4 modelMatrix;
        mat4 viewMatrix;
        ShaderProgram prog;
        GLuint vertexArrayID;
        GLuint vertexbuffer;
        GLuint normalbuffer;
        SDL_Window *mainwindow;
        CAssimpModel objModel;
};

#endif // CGL_H
