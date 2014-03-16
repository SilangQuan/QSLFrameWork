#include "cgl.h"

CGL::CGL()
{
    //ctor

}

CGL::CGL(int _width, int _height, SDL_Window *w):prog(),objModel(prog)
{
    this->width = _width;
    this->height = _height;
    mainwindow = w;
}

CGL::~CGL()
{
    //dtor
}

bool CGL::initGL()
{
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    modelMatrix = mat4(1.0f);
    viewMatrix = glm::lookAt(vec3(0.0f,0.0f,10.0f), vec3(0.0f,2.0f,0.0f), vec3(0.0f,1.0f,0.0f));

    objModel.LoadModelFromFile("../assets/model/bunny.obj");
    return true;
}

bool CGL::resizeGL(int width,int height)
{
    if ( height == 0 )
    {
        height = 1;
    }
    //Reset View
    glViewport( 0, 0, (GLint)width, (GLint)height );
    //Choose the Matrix mode
    glMatrixMode( GL_PROJECTION );
    //reset projection
    glLoadIdentity();
    //set perspection
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 1000.0 );
    //choose Matrix mode
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
}

bool CGL::renderGL()
{
    /* These are to calculate our fps */
    static GLint T0     = 0;
    static GLint Frames = 0;
    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );

    objModel.render();
    //objModel.renderModel();

    SDL_GL_SwapWindow(mainwindow);

    //this->changeMatrics();
    /* Gather our frames per second */
    Frames++;
    {
        GLint t = SDL_GetTicks();
        if (t - T0 >= 5000) {
            GLfloat seconds = (t - T0) / 1000.0;
            GLfloat fps = Frames / seconds;
            printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
            T0 = t;
            Frames = 0;
        }
        //SDL just render too fast!
        SDL_Delay(10);
    }

}

void CGL::compileShader()
{

    if( ! prog.compileShaderFromFile("../shader/without_texture.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("../shader/without_texture.frag",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }

    prog.bindAttribLocation(0, "VertexPosition");
    prog.bindAttribLocation(1, "VertexNormal");

    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.validate() )
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }
    prog.use();
}

void CGL::changeMatrics()
{
    this->modelMatrix = glm::rotate(this->modelMatrix, 1.0f, vec3(0.0f,1.0f,0.0f));
    mat4 mv = viewMatrix * modelMatrix;
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    prog.setUniform("MVP", projection * mv);
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
}

void CGL::setUniform()
{
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f,1000.0f);
    mat4 mv = viewMatrix * modelMatrix;

    prog.setUniform("Kd", 0.0f, 0.9f, 0.9f);
    prog.setUniform("Ld", 1.0f, 0.5f, 0.5f);
    prog.setUniform("LightPosition", viewMatrix * vec4(-5.0f,220.0f,215.0f,1.0f) );
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
    prog.setUniform("MVP", projection * mv);


}

void CGL::clean()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &normalbuffer);
    prog.deleteProgram();
    glDeleteVertexArrays(1, &vertexArrayID);
}

bool CGL::fileExists( const string & fileName )
{
    struct stat info;
    int ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}

