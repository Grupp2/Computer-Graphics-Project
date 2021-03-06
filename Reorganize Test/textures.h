#ifndef TEXTURES_H_
#define TEXTURES_H_

#include <GL/glut.h>
#include "exceptioninfo.h"
#include "imagefile.h"

extern GLuint texture_brickwall;
extern GLuint texture_floor;
extern GLuint texture_door;
extern GLuint texture_grass;
extern GLuint texture_sky;
extern GLuint texture_wall;
extern GLuint texture_glass;
extern GLuint texture_roof;
extern GLuint texture_wallpaper;

void loadTextures();

#endif
