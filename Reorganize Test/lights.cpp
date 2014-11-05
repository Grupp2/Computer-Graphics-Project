#include "lights.h"

void spotlight() {
	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat spotDirection[] = { 0.0, 0.0, -1.0 };
	GLfloat lightDiffuseSpecular[] = { 0.94, 0.9, 0.8, 0.0 };
	GLfloat lightAmbient[] = { 0.47, 0.45, 0.4, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseSpecular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDiffuseSpecular);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.5);

}

void light1(GLfloat *col1, GLfloat *col2, GLfloat *col3) {
	GLfloat lightPos[4] = {
		6.0, -7.0, -10.0, 1.0
	};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, col1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
}

void light2(GLfloat *col1, GLfloat *col2, GLfloat *col3) {
	GLfloat lightPos[4] = {
		10.0, 7.9, 10.0, 1.0
	};
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, col2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col3);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col1);
}

void light3(GLfloat *col1, GLfloat *col2, GLfloat *col3) {
	GLfloat lightPos[4] = {
		0.0, 7.9, -10.0, 1.0
	};
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, col3);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col1);
}

void enableLights()
{
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}
void addLightColors() {
	GLfloat lightColor1[4] = {
		0.1, 0.1, 0.1, 1.0
	};
	GLfloat lightColor2[4] = {
		0.5, 0.5, 0.5, 0.5
	};
	GLfloat lightColor3[4] = {
		0.2, 0.2, 0.2, 0.2
	};
	light1(lightColor1, lightColor2, lightColor3);
	//light2(lightColor1, lightColor2, lightColor3);
	//light3(lightColor1, lightColor2, lightColor3);
}

void disableLights()
{
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
}

void enableSpotlight()
{
	glEnable(GL_LIGHT0);
}

void disableSpotlight()
{
	glDisable(GL_LIGHT0);
}
