#ifndef UTIL_H
#define UTIL_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_image.h>
#include <fstream>
using std::ifstream;
using std::ios;

#include <sstream>
using std::ostringstream;

#include <sys/stat.h>

using namespace std;

class Util
{
public:
    Util();
    virtual ~Util();
    char *textFileRead(char *fn);
protected:
private:
};

#endif // UTIL_H
