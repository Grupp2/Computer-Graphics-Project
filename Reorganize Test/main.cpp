/*
*  Computer Graphics
*  Practical 4
*  practical4.cpp
*
*  Peter Jenke, 2012
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <GL/glut.h>
#include "imagefile.h"
#include "exceptioninfo.h"
#include <math.h>
#include "drawing.h"
#include "house.h"
#include "textures.h"
#include "door.h"
#include <iostream>
#include "skybox.h"
#include "lights.h"

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=5.0f;

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


GLfloat ambientMtrl[4] = {
	0.1, 0.1, 0.1, 1.0
};

GLfloat diffuseMtrl[4] = {
	0.35, 0.55, 0.35, 1.0
};

float ctrl_delta = 0.01;

char s[30], buf[100];
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void resetPerspectiveProjection() {
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}

void setfont(char* name, int size) {
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

void draw_string(float x, float y, char *string) {
	//char *s;
	int i = 0;

	glRasterPos2f(x, y);
	while (string[i] != '\0') {
		glutBitmapCharacter(font_style, string[i]);
		i++;
	}
}

void do_idle() {
	glutPostRedisplay();
}

void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(55.0, (double)(width) / (double)(height), 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void addTeapot() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(-10.0, -4.0, -30.0);
		glRotatef(teapotAngle, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMtrl);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMtrl);
		glutSolidTeapot(1.0);
	glPopMatrix();
	if (teapotAngle == 360.0)
		teapotAngle = 0.0;
	else
		teapotAngle += 1.0;
};

void addMtrl() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMtrl);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMtrl);
}


void drawDoors()
{
	drawDoor(15, 0, 0);
	drawDoor(5, 0, -15);
	drawDoor(25, 0, -15);
	drawDoor(15, 0, -20);
}

void drawGarden() {
	float textures_container[] = { texture_grass, texture_brickwall, texture_floor };

	int leftSideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		1, // right
		0, // roof
		1 // ground
	};
	float leftSegment[3] = {
		150, 5, 150
	};

	drawCube(leftSegment, leftSideSelector, textures_container);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	
	spotlight();

	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

	//addLights();
	//addMtrl();
	//addTeapot();

	glTranslatef(-2, -5, -20);
	
	glPushMatrix();
		glTranslatef(-500.0, -500.0, -500.0);
		drawSkybox();
	glPopMatrix();



	glPushMatrix();
		glTranslatef(-75, -0.1, 75);
		drawGarden();
	glPopMatrix();


	glPushMatrix();
			glTranslatef(-17.5, 0, 17.5);
			drawDoors();
			drawHouse();
	glPopMatrix();
	
	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y) {
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
	default:
		// do nothing...
		break;
	}
}

void special_buttons(int key, int xx, int yy) {
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

void mouse_motion(int x, int y) {
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

void ctrl_point_menu(int value) {
	switch (value) {
	case 'a':
		break;
	case 'b':
		break;
	case 'c':
		break;
	case 'd':
		break;
	default:
		// do nothing...
		break;
	}
}

void getimagefromfile(const char *src, GLuint *texname) 
{
	// Step 1: Create an instance of class ImageFile:
	ImageFile* ifile;
	try {
		ifile = new ImageFile (src, 0);
	} catch (ExceptionInfo ei) {
		throw ei;
	}
	// Step 2: How many bits per pixel?
	// If 24: Image without alpha channel, i.e. RGB image.
	// If 32: Image with alpha channel, i.e. RGBA image.
	GLenum img_type = GL_RGBA;
	if (ifile->getBPP() == 24)
	img_type = GL_RGB;
	// Step 3: Create and bind a texture object
	glGenTextures (1, texname);
	glBindTexture (GL_TEXTURE_2D, *texname);
	// Step 4: Set texture parameters (wrapping etc.)
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Step 5: Assign the data from the image file to the texture object:
	glTexImage2D (GL_TEXTURE_2D, 0, 3, ifile->getWidth(),
			ifile->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, ifile->getData());
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	// Step 6: Unbind the texture object.
	glBindTexture (GL_TEXTURE_2D, 0);
}

void loadTextures()
{
	getimagefromfile("brickwall_2.bmp", &texture_brickwall);
	getimagefromfile("floor.bmp", &texture_floor);
	getimagefromfile("fancy_door.bmp", &texture_door);
	getimagefromfile("grass_3.bmp", &texture_grass);
	getimagefromfile("sky.bmp", &texture_sky);
	getimagefromfile("plaster_texture.bmp", &texture_wall);
	getimagefromfile("glass.bmp", &texture_glass);
	getimagefromfile("roof.bmp", &texture_roof);
}

void init(void) {
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(do_idle);
	glutKeyboardFunc(buttons);
	glutSpecialFunc(special_buttons);
	glutMotionFunc(mouse_motion);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer Graphics, Project");
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_FUNC_ADD);
	loadTextures();
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();
	return 0;
}

