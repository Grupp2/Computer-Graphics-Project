#ifndef DRAWING_H_
#define DRAWING_H_

#include <GL/glut.h>
#include <glm/glm.hpp>

void drawCube(float endPoint[3], int sideSelector[6], GLuint *texture_container, bool isOuterwall);
void drawQuad(float arr[][3], GLuint texture, GLfloat *normVec);

#endif