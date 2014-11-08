#include "lights.h"

LightCoords l1coord;
LightCoords l2coord;
LightCoords l3coord;
LightCoords *selectedLight;

void spotlight()
{
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

void light1()
{
	GLfloat lightColor1[4] = {
		0.1, 0.1, 0.1, 1.0
	};
	GLfloat lightColor2[4] = {
		0.5, 0.5, 0.5, 0.5
	};
	GLfloat lightPos[4] = {
		l1coord.x, l1coord.y, l1coord.z, l1coord.w
	};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightColor1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor2);
}

void light2()
{
	GLfloat lightColor1[4] = {
		0.1, 0.1, 0.1, 1.0
	};
	GLfloat lightColor2[4] = {
		0.8, 0.5, 0.5, 1.0
	};
	GLfloat lightPos[4] = {
		l2coord.x, l2coord.y, l2coord.z, l2coord.w
	};
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightColor1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor2);
}

void light3()
{
	GLfloat lightColor1[4] = {
		0.1, 0.1, 0.1, 1.0
	};
	GLfloat lightColor2[4] = {
		0.5, 0.8, 0.5, 1.0
	};
	GLfloat lightPos[4] = {
		l3coord.x, l3coord.y, l3coord.z, l3coord.w
	};
	glLightfv(GL_LIGHT3, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT3, GL_AMBIENT, lightColor1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor2);
}

void enableLights()
{
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
}
void addLights() {

	light1();
	light2();
	light3();
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

void selectLight(int i)
{
	switch (i) {
	case 1:
		selectedLight = &l1coord;
		break;
	case 2:
		selectedLight = &l2coord;
		break;
	case 3:
		selectedLight = &l3coord;
		break;
	}
}

void getLightCoord(int i, LightCoords& o)
{
	switch (i) {
	case 1:
		o = l1coord;
		return;
	case 2:
		o = l2coord;
		return;
	case 3:
		o = l3coord;
		return;
	}
}

void initializeLights()
{
	//Default
	selectedLight = &l2coord;
	//Light 1
	l1coord.x = 8.0;
	l1coord.y = 6;
	l1coord.z = -8.0;
	l1coord.w = 1.0;

	//Light 2
	l2coord.x = 30.0;
	l2coord.y = 6;
	l2coord.z = -8.0;
	l2coord.w = 1.0;

	//Light 3
	l3coord.x = 19.5;
	l3coord.y = 6;
	l3coord.z = -35.0;
	l3coord.w = 1.0;
}

LightCoords* getSelectedLight()
{
	return selectedLight;
}

