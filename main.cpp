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

float OuterPositions[8][3] = {
		{ -50.0, 00.0, -50.0 }, /* 0 */
		{ -50.0, 50.0, -50.0 }, /* 1 */
		{ 50.0, 50.0, -50.0 },	/* 2 */
		{ 50.0, 00.0, -50.0 },	/* 3 */
		{ -50.0, 00.0, 50.0 },	/* 4 */
		{ -50.0, 50.0, 50.0 },	/* 5 */
		{ 50.0, 50.0, 50.0 },	/* 6 */
		{ 50.0, 00.0, 50.0 }	/* 7 */
};

float WallPositions[4][3] = {
		{ -50.0, 00.0, -50.0 }, /* 0 */
		{ -50.0, 50.0, -50.0 }, /* 1 */
		{ 50.0, 50.0, -50.0 },	/* 2 */
		{ 50.0, 00.0, -50.0 }	/* 3 */
};

float InnerPositions[8][3] = {
		{ -30.0, 00.0, -30.0 }, /* 0 */
		{ -30.0, 20.0, -30.0 }, /* 1 */
		{ 30.0, 20.0, -30.0 },	/* 2 */
		{ 30.0, 00.0, -30.0 },	/* 3 */
		{ -30.0, 00.0, 30.0 },	/* 4 */
		{ -30.0, 20.0, 30.0 },	/* 5 */
		{ 30.0, 20.0, 30.0 },	/* 6 */
		{ 30.0, 00.0, 30.0 }	/* 7 */

};
		
int indices[12][3] = {
		{ 0, 4, 1 }, { 4, 5, 1 },
		{ 0, 3, 2 }, { 0, 1, 2 },
		{ 3, 7, 6 }, { 3, 2, 6 },
		{ 4, 5, 7 }, { 5, 7, 6 },
		{ 0, 4, 7 }, { 0, 3, 7 },
		{ 2, 5, 6 }, { 1, 2, 5 }
};


GLuint texture_brickwall;
GLuint texture_floor;

GLfloat colors[3][3] = { 
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 1.0, 1.0, 0.0 } 
};

float ctrl_delta = 0.01;

char s[30], buf[100];
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;


void setOrthographicProjection() {
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





void drawQuad_XY(float arr[][3], GLuint texture) {
	for (int b = arr[0][1]; b < arr[2][1]; b++)	{
		for (int i = arr[0][0]; i < arr[1][0]; i++) {
			glColor3f(1, 0, 0);

			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(i, b, 0);
			glTexCoord2f(1, 0);
			glVertex3f(i + 1, b, 0);

			glTexCoord2f(1, 1);
			glVertex3f(i + 1, b + 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(i, b + 1, 0);

			glEnd();
		}
	}
}

void drawQuad_XZ(float arr[][3], GLuint texture) {
	for (int b = arr[0][2]; b < arr[2][2]; b++) {
		for (int i = arr[0][0]; i < arr[1][0]; i++) {
			glColor3f(1, 0, 0);

			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(i, b, 0);
			glTexCoord2f(1, 0);
			glVertex3f(i + 1, b, 0);

			glTexCoord2f(1, 1);
			glVertex3f(i + 1, b + 1, 0);
			glTexCoord2f(0, 1);
			glVertex3f(i, b + 1, 0);

			glEnd();
		}
	}
}

void drawQuad_YZ(float arr[][3], GLuint texture) {
	for (int b = arr[0][2]; b < arr[2][2]; b++) {
		for (int i = arr[0][0]; i < arr[1][0]; i++)	{
			glColor3f(1, 0, 0);

			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);

			glTexCoord2f(0, 0);
			glVertex3f(i, arr[0][1], b);
			glTexCoord2f(1, 0);
			glVertex3f(i + 1, arr[1][1], b);

			glTexCoord2f(1, 1);
			glVertex3f(i + 1, arr[3][1], b + 1);
			glTexCoord2f(0, 1);
			glVertex3f(i, arr[2][1], b + 1);

			glEnd();
		}
	}
}

void drawCube(float endPoint[3], int sideSelector[6]) {

	float frontbackarr[4][3] = {
			{ 0.0, 0.0, 0.0 },
			{ endPoint[0], 0.0, 0.0 },
			{ 0.0, endPoint[1], 0.0 },
			{ endPoint[0], endPoint[1], 0.0 }
	};

	float leftrightarr[4][3] = {
			{ 0.0, 0.0, 0.0 },
			{ endPoint[2], 0.0, 0.0 },
			{ 0.0, endPoint[1], 0.0 },
			{ endPoint[2], endPoint[1], 0.0 }
	};

	float roofgroundarr[4][3] = {
			{ 0.0, 0.0, 0.0 },
			{ endPoint[0], 0.0, 0.0 },
			{ 0.0, endPoint[2], 0.0 },
			{ endPoint[0], endPoint[2], 0.0 }
	};


	glPushMatrix();
	if (sideSelector[0] == 1) {
		glPushMatrix(); // Back
			glTranslatef(0.0, 0.0, -endPoint[2]);
			drawQuad_XY(frontbackarr, texture_brickwall);
		glPopMatrix();
	}
	if (sideSelector[1] == 1) {
		glPushMatrix(); // front
		glTranslatef(0.0, 0.0, 0.0);
		drawQuad_XY(frontbackarr, texture_brickwall);
		glPopMatrix();
	}
	if (sideSelector[2] == 1) {
		glPushMatrix(); // left
		glRotatef(90, 0.0, 1.0, 0.0);
		drawQuad_XY(leftrightarr, texture_brickwall);
		glPopMatrix();
	}
	if (sideSelector[3] == 1) {
		glPushMatrix(); // right
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[0]);
		drawQuad_XY(leftrightarr, texture_brickwall);
		glPopMatrix();
	}
	if (sideSelector[4] == 1) {
		glPushMatrix(); // roof
		glRotatef(270, 1.0, 0.0, 0.0);
		drawQuad_XY(roofgroundarr, texture_floor);
		glPopMatrix();
	}
	if (sideSelector[5] == 1) {
		glPushMatrix(); // ground
		glRotatef(270, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[1]);
		drawQuad_XY(roofgroundarr, texture_floor);
		glPopMatrix();
	}
	glPopMatrix();

}

void drawCube() {

	float arr[4][3] = {
			{ 0, 0, 0 }, { 10, 0, 0 }, { 0, 10, 0 }, { 10, 10, 0 }
	};
	glPushMatrix();
		glPushMatrix(); // Back
			glTranslatef(0.0, 0.0, -arr[1][0]);
			drawQuad_XY(arr, texture_brickwall);
		glPopMatrix();

		glPushMatrix(); // front
			glTranslatef(0.0, 0.0, 0.0);
			drawQuad_XY(arr, texture_brickwall);
		glPopMatrix();

		glPushMatrix(); // left
			glRotatef(90, 0.0, 1.0, 0.0);
			drawQuad_XY(arr, texture_brickwall);
		glPopMatrix();

		glPushMatrix(); // right
			glRotatef(90, 0.0, 1.0, 0.0);
			glTranslatef(0.0, 0.0, arr[1][0]);
			drawQuad_XY(arr, texture_brickwall);
		glPopMatrix();

		glPushMatrix(); // roof
			glRotatef(270, 1.0, 0.0, 0.0);
			drawQuad_XY(arr, texture_floor);
		glPopMatrix();

		glPushMatrix(); // floor
			glRotatef(270, 1.0, 0.0, 0.0);
			glTranslatef(0.0, 0.0, arr[1][0]);
			drawQuad_XY(arr, texture_floor);
		glPopMatrix();

	glPopMatrix();
}

void smallRoom() {
	float leftSegment[3] = {
		5 ,8 ,15
	};

	float MiddleSegment[3] = {
		5, 8, 15
	};

	float rightSegment[3] = {
		5, 8, 15
	};

}

void largeRoom() {
	float leftSegment[3] = {
		15, 8, 15
	};

	float MiddleSegment[3] = {
		5, 8, 15
	};

	float rightSegment[3] = {
		15, 8, 15
	};
}

void smallCorridore() {
	float segment[3] = {
		5, 8, 15
	};
}

void largeCorridore() {
	float segment[3] = {
		35, 8, 5
	};
}


void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

	glTranslatef(-2, -5, -20);
	//glRotatef(30, 0, 1, 0);

	float endPoint[3] = {
		50, 10, 50
	};

	

	int sideSelector[6] = {
		1, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	drawCube(endPoint, sideSelector);
	/*
	float arr[4][3] = {
				{0, 0, 0}, {10, 0, 0}, {0, 10, 0}, {10, 10, 0}
		};

	drawQuad_XY(arr, texture_brickwall);

	float roof[4][3] = {
					{0, 10, 0}, {10, 10, 0}, {0, 10, 10}, {10, 10, 10}
	};
	drawQuad_YZ(roof, texture_brickwall);
	*/
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

void init(void) {
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(do_idle);
	glutKeyboardFunc(buttons);
	glutSpecialFunc(special_buttons);
	glutMotionFunc(mouse_motion);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}



void getimagefromfile(const char *src, GLuint *texname) {
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
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// Step 6: Unbind the texture object.
	glBindTexture (GL_TEXTURE_2D, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer Graphics, Project");
	glEnable(GL_TEXTURE_2D);
	getimagefromfile("brickwall.tif", &texture_brickwall);
	getimagefromfile("floor.tif", &texture_floor);
	init();

	glutMainLoop();
	return 0;
}

