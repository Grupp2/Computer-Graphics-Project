#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <GL/glut.h>

struct LightCoords
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};


void spotlight();
void light1(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void light2(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void light3(GLfloat *col1, GLfloat *col2, GLfloat *col3);
void enableLights();
void addLights();
void disableLights();
void enableSpotlight();
void disableSpotlight();
void selectLight(int i);
void initializeLights();
void getLightCoord(int i, LightCoords& o);
LightCoords* getSelectedLight();

#endif