#ifndef CTEXTURE_H
#define CTEXTURE_H

#include "util.h"
#include <SDL2/SDL_image.h>

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

/********************************
Class:		CTexture

Purpose:	Wraps OpenGL texture object and performs their loading.
********************************/

class CTexture
{
public:
    CTexture();
    CTexture(GLenum TextureTarget, const std::string& FileName);

    bool load();
    void bind(GLenum TextureUnit = 0);

    void setFiltering(int a_tfMagnification, int a_tfMinification);
    void setSamplerParameter(GLenum parameter, GLenum value);


    int getWidth();
    int getHeight();
    int getBPP();
    string getPath();
    unsigned char getTextureID();

    void deleteTexture();
    bool hasLoaded();



private:
    SDL_Surface* surface;
    int width, height, bpp; // Texture width, height, and bytes per pixel
    GLenum textureTarget;
    GLuint textureObj;
    string fileName;
    int mode;
    bool isLoaded;
};

#endif
