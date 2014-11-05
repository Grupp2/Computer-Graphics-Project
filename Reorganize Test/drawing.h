#ifndef DRAWING_H_
#define DRAWING_H_

#include <GL/glut.h>
#include <glm/glm.hpp>

extern GLfloat normalVectors[6][3];


void drawCube(float endPoint[3], int sideSelector[6], float *texture_container);
void drawQuad(float arr[][3], GLuint texture, GLfloat *normVec);

glm::vec3 computeNormal(
glm::vec3 const & a, 
glm::vec3 const & b,
glm::vec3 const & c);
#endif