#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <GL/glut.h>

void spotlight();
void light1(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void light2(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void light3(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void enableLights();
void addLightColors();
void disableLights();
void enableSpotlight();
void disableSpotlight();

#endif