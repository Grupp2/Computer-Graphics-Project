#ifndef DOOR_H_
#define DOOR_H_

#include <GL/glut.h>
#include "textures.h"
#include "material.h"

extern bool isOpen;
extern bool isActive;
extern float doorAngle;

void drawDoor(float x, float y, float z);
void rotateDoor(float x, float y, float z);
void setisactive(bool xstate);

#endif