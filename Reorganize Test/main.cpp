/*
*  Computer Graphics
*  Practical 4
*  practical4.cpp
*
*  Peter Jenke, 2012
*/

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>

#include "door.h"
#include "garden.h"
#include "house.h"
#include "lights.h"
#include "material.h"
#include "skybox.h"
#include "textures.h"

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;
float y=1.0;

float theta = 0.0;
float phi = 0.0;

float alpha = 0.0;
float angle_delta = 0.5;

// The previous mouse position:
int x_prev = 0;
int y_prev = 0;

int w = 800;
int h = 600;

float teapotAngle = 0.0;
bool renderInfo = false;

float ctrl_delta = 0.01;

char s[30], buf[100];
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void resetPerspectiveProjection()
{
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}

void setfont(char* name, int size)
{
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12)
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
	}
	else if (strcmp(name, "times roman") == 0) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	}
	else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
	}
	else if (strcmp(name, "9x15") == 0) {
		font_style = GLUT_BITMAP_9_BY_15;
	}
}

void draw_string(float x, float y, const char *string)
{
	//char *s;
	int i = 0;

	glRasterPos2f(x, y);
	while (string[i] != '\0') {
		glutBitmapCharacter(font_style, string[i]);
		i++;
	}
}

void setOrthographicProjection()
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the 
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, w, 0, h);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// move the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void render_info()
{
	float white[] = { 1.0, 1.0, 1.0 };

	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
	setfont("8x13", 20);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();

	LightCoords l1;
	getLightCoord(1, l1);

	LightCoords l2;
	getLightCoord(2, l2);

	LightCoords l3;
	getLightCoord(3, l3);

	glColor3fv(white);
	draw_string(30, 20, "Light 1 (Position is relative to house)");
#ifdef _WIN32
	sprintf_s(buf, "Position:  x: %.2f y: %.2f z: %.2f", l1.x, l1.y, l1.z);
#endif
#ifdef __linux__
	sprintf(buf, "Position:  x: %.2f y: %.2f z: %.2f", l1.x, l1.y, l1.z);
#endif
	draw_string(30, 40, buf);

	glColor3fv(white);
	draw_string(30, 60, "Light 2 (Position is relative to house)");
#ifdef _WIN32
	sprintf_s(buf, "Position:  x: %.2f y: %.2f z: %.2f", l2.x, l2.y, l2.z);
#endif
#ifdef __linux__
	sprintf(buf, "Position:  x: %.2f y: %.2f z: %.2f", l2.x, l2.y, l2.z);
#endif
	draw_string(30, 80, buf);

	glColor3fv(white);
	draw_string(30, 100, "Light 3 (Position is relative to house)");
#ifdef _WIN32
	sprintf_s(buf, "Position:  x: %.2f y: %.2f z: %.2f", l3.x, l3.y, l3.z);
#endif
#ifdef __linux__
	sprintf(buf, "Position:  x: %.2f y: %.2f z: %.2f", l3.x, l3.y, l3.z);
#endif
	draw_string(30, 120, buf);


	glPopMatrix();
	resetPerspectiveProjection();
	glEnable(GL_LIGHTING);
}


void do_idle()
{
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(55.0, (double)(width) / (double)(height), 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void addTeapot() {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(8.0, 2.0, -8.0);
		glRotatef(teapotAngle, 0.0, 1.0, 0.0);
		addMaterial();
		glutSolidTeapot(1.0);
	glPopMatrix();
	if (teapotAngle == 360.0)
		teapotAngle = 0.0;
	else
		teapotAngle += 1.0;
	glPopAttrib();
};



void drawDoors()
{
	drawDoor(17, 0, 0);
	drawDoor(6, 0, -16);
	drawDoor(28, 0, -16);
	drawDoor(17, 0, -27);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_LIGHT0);

	spotlight();

	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	glTranslatef(-2, -3, -25);

	glPushMatrix();
		glTranslatef(-500.0, -500.0, -500.0);
		drawSkybox();
	glPopMatrix();



	glPushMatrix();
		glTranslatef(-75, -0.1, 75);
		drawGarden();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(-17.5, 0, 22);
		drawDoors();
		addTeapot();
		addLights();
		drawHouse();
	glPopMatrix();

	if (renderInfo)
		render_info();

	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'x':
		// decrease x-component of active control point
		break;
	case 'X':
		// increase x-component of active control point

		break;
	case 'y':
		// decrease y-component of active control point

		break;
	case 'Y':
		// increase y-component of active control point

		break;
	case 'z':
		// decrease z-component of active control point

		break;
	case 'Z':
		// increase z-component of active control point

		break;
	case 'o':
		setisactive(true);
		break;
	case 's':
		disableSpotlight();
		break;
	case 'S':
		enableSpotlight();
		break;
	case 'u':
		getSelectedLight()->x += 0.1;
		break;
	case 'U':
		getSelectedLight()->x -= 0.1;
		break;
	case 'j':
		getSelectedLight()->y += 0.1;
		break;
	case 'J':
		getSelectedLight()->y -= 0.1;
		break;
	case 'm':
		getSelectedLight()->z += 0.1;
		break;
	case 'M':
		getSelectedLight()->z -= 0.1;
		break;
	case 'i':
		renderInfo = !renderInfo;
		break;
	case 'L':
		enableLights();
		break;
	case 'l':
		disableLights();
		break;
	default:
		// do nothing...
		break;
	}
}

void special_buttons(int key, int xx, int yy)
{
	float fraction = 0.5f;

		switch (key) {
			case GLUT_KEY_LEFT :
				angle -= 0.05f;
				lx = sin(angle);
				lz = -cos(angle);
				break;
			case GLUT_KEY_RIGHT :
				angle += 0.05f;
				lx = sin(angle);
				lz = -cos(angle);
				break;
			case GLUT_KEY_UP :
				x += lx * fraction;
				z += lz * fraction;
				break;
			case GLUT_KEY_DOWN :
				x -= lx * fraction;
				z -= lz * fraction;
				break;
		}
}

void mouse_motion(int x, int y)
{
	if (x_prev < x)
		theta += angle_delta;
	else
		theta -= angle_delta;

	if (y_prev < y)
		phi += angle_delta;
	else
		phi -= angle_delta;

	if (theta > 360.0)
		theta -= 360.0;

	if (phi > 360.0)
		phi -= 360.0;

	x_prev = x;
	y_prev = y;
}

void light_point_menu(int value)
{
	switch (value) {
	case 'a':
		selectLight(1);
		break;
	case 'b':
		selectLight(2);
		break;
	case 'c':
		selectLight(3);
		break;
	default:
		// do nothing...
		break;
	}
}

void init(void)
{
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(do_idle);
	glutKeyboardFunc(buttons);
	glutSpecialFunc(special_buttons);
	glutMotionFunc(mouse_motion);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glutCreateMenu(light_point_menu);
	glutAddMenuEntry("Choose Light:", 0);
	glutAddMenuEntry("Light 1", 'a');
	glutAddMenuEntry("Light 2", 'b');
	glutAddMenuEntry("Light 3", 'c');
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer Graphics, Project");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	loadTextures();
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	initializeLights();
	enableLights();
	init();
	glutMainLoop();
	return 0;
}

