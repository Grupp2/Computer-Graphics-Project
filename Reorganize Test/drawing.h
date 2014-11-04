#ifndef DRAWING_H_
#define DRAWING_H_

#include <GL/glut.h>

extern GLfloat normalVectors[6][3];

void drawCube(float endPoint[3], int sideSelector[6], float *texture_container);
void drawQuad(float arr[][3], GLuint texture, GLfloat *normVec);

#endif