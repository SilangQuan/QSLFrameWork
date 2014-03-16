#include "ctexture.h"

CTexture::CTexture()
{
    isLoaded = false;
}

CTexture::CTexture(GLenum target, const string& f)
{
    textureTarget = target;
    fileName = f;
    isLoaded = false;
    surface = NULL;
}

bool CTexture::load()
{
    glEnable(GL_TEXTURE_2D);

    glGenTextures(1, &textureObj);
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    cout<<fileName<<endl;

    if (surface == NULL) { //If it failed, say why and don't continue loading the texture
        cout<<"Error:" <<SDL_GetError()<<endl;
        return 0;
    }

    width = surface->w;
    height = surface->h;
    bpp = surface->pitch;

    // work out what format to tell glTexImage2D to use...
    if (surface->format->BytesPerPixel == 3) { // RGB 24bit
        mode = GL_RGB;
    } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit
        mode = GL_RGBA;
    } else {
        SDL_FreeSurface(surface);
        return false;
    }

    glBindTexture(textureTarget, textureObj);
    glTexImage2D(textureTarget, 0, mode, surface->w,surface->h, 0, mode,GL_UNSIGNED_BYTE,surface->pixels);
    setFiltering( GL_LINEAR,GL_LINEAR);

    isLoaded = true;

    if(surface) SDL_FreeSurface(surface);


    return true;
}

// Sets magnification and minification texture filter.

void CTexture::setFiltering(int a_tfMagnification, int a_tfMinification)
{
    glTexParameteri(textureTarget,GL_TEXTURE_MIN_FILTER,a_tfMinification);
    glTexParameteri(textureTarget,GL_TEXTURE_MAG_FILTER,a_tfMagnification);
}

void CTexture::bind(GLenum textureUnit)
{
    glActiveTexture(textureUnit);
    glBindTexture(textureTarget, textureObj);
}

/*-----------------------------------------------

Name:	DeleteTexture

Params:	none

Result:	Frees all memory used by texture.

/*---------------------------------------------*/

void CTexture::deleteTexture()
{
    if(surface) SDL_FreeSurface(surface);
}


int CTexture::getWidth()
{
    return width;
}

int CTexture::getHeight()
{
    return height;
}

int CTexture::getBPP()
{
    return bpp;
}

unsigned char CTexture::getTextureID()
{
    return textureObj;
}

string CTexture::getPath()
{
    return fileName;
}

bool CTexture::hasLoaded()
{
    return isLoaded;
}
