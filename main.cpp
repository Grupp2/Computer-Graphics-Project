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

bool isOpen = false;
bool isActive = false;
float doorAngle = 0.0;

GLuint texture_brickwall;
GLuint texture_floor;
GLuint texture_door;
GLuint texture_grass;
GLuint texture_sky;
GLuint texture_wall;
GLuint texture_glass;
GLuint texture_roof;

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

void light1(GLfloat *col1, GLfloat *col2, GLfloat *col3) {
	GLfloat lightPos[4] = {
		-10.0, 7.9, 10.0, 1.0
	};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, col1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col3);
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

void addLights() {
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	GLfloat lightColor1[4] = {
		1.0, 1.0, 1.0, 0.6
	};
	GLfloat lightColor2[4] = {
		0.0, 0.5, 0.5, 0.5
	};
	GLfloat lightColor3[4] = {
		0.2, 0.7, 0.1, 0.3
	};
	light1(lightColor1, lightColor2, lightColor3);
	light2(lightColor1, lightColor2, lightColor3);
	light3(lightColor1, lightColor2, lightColor3);
}

void addTeapot() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(-10.0, 0.0, -30.0);
		glutSolidTeapot(1.0);
	glPopMatrix();
};

void addMtrl() {
	GLfloat ambientMtrl[4] = {
		0.1, 0.1, 0.1, 1.0
	};

	GLfloat diffuseMtrl[4] = {
		0.35, 0.55, 0.35, 1.0
	};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMtrl);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMtrl);
}

void drawQuad_XY(float arr[][3], GLuint texture) {

	for (int b = arr[0][1]; b < arr[2][1]; b++)	{
		for (int i = arr[0][0]; i < arr[1][0]; i++) {
			glColor3f(1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(i, b, 0);
			glTexCoord2f(1.0, 0);
			glVertex3f(i + 1, b, 0);

			glTexCoord2f(1.0, 1.0);
			glVertex3f(i + 1, b + 1, 0);
			glTexCoord2f(0, 1.0);
			glVertex3f(i, b + 1, 0);

			glEnd();
		}
	}
}

void drawCube(float endPoint[3], int sideSelector[6], float *texture_container) {

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
			drawQuad_XY(frontbackarr, texture_container[1]);
		glPopMatrix();
	}
	if (sideSelector[1] == 1) {
		glPushMatrix(); // front
		glTranslatef(0.0, 0.0, 0.0);
		drawQuad_XY(frontbackarr, texture_container[1]);
		glPopMatrix();
	}
	if (sideSelector[2] == 1) {
		glPushMatrix(); // left
		glRotatef(90, 0.0, 1.0, 0.0);
		drawQuad_XY(leftrightarr, texture_container[1]);
		glPopMatrix();
	}
	if (sideSelector[3] == 1) {
		glPushMatrix(); // right
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[0]);
		drawQuad_XY(leftrightarr, texture_container[1]);
		glPopMatrix();
	}
	if (sideSelector[4] == 1) {
		glPushMatrix(); // roof
		glRotatef(270, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[1]);
		drawQuad_XY(roofgroundarr, texture_container[2]);
		glPopMatrix();
	}
	if (sideSelector[5] == 1) {
		glPushMatrix(); // ground
		glRotatef(270, 1.0, 0.0, 0.0);
		drawQuad_XY(roofgroundarr, texture_container[0]);
		glPopMatrix();
	}
	glPopMatrix();

}

void smallRoom() {
	float textures_container[] = { texture_floor, texture_wall, texture_floor };

	int leftSideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		0, // right
		1, // roof
		1 // ground
	};
	float leftSegment[3] = {
		5 ,8 ,15
	};



	drawCube(leftSegment, leftSideSelector, textures_container);

	int middleSideSelector[6] = {
		0, // Back
		1, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};
	float MiddleSegment[3] = {
		5, 8, 15
	};

	glPushMatrix();
	glTranslatef(5, 0, 0);
	drawCube(MiddleSegment, middleSideSelector, textures_container);
	glPopMatrix();
	int rightSideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		1, // right
		1, // roof
		1 // ground
	};
	float rightSegment[3] = {
		5, 8, 15
	};
	glPushMatrix();
	glTranslatef(10, 0, 0);
	drawCube(rightSegment, rightSideSelector, textures_container);
	glPopMatrix();
}

void largeRoom() {
	float textures_container[] = { texture_floor, texture_wall, texture_floor };

	
	int leftSideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		0, // right
		1, // roof
		1 // ground
	};

	float leftSegment[3] = {
		15, 8, 15
	};

	drawCube(leftSegment, leftSideSelector, textures_container);

	int middleSideSelector[6] = {
		0, // Back
		0, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	float MiddleSegment[3] = {
		5, 8, 15
	};

	glPushMatrix();
	glTranslatef(15, 0, 0);
	drawCube(MiddleSegment, middleSideSelector, textures_container);
	glPopMatrix();

	int rightSideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		1, // right
		1, // roof
		1 // ground
	};

	float rightSegment[3] = {
		15, 8, 15
	};

	glPushMatrix();
	glTranslatef(20, 0, 0);
	drawCube(rightSegment, rightSideSelector, textures_container);
	glPopMatrix();
}

void drawWindow()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	glTranslatef(15, 0, -35);

	GLfloat windowMtrl[4] = {
		0.0, 0.0, 0.0, 0.5
	};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, windowMtrl);

	glBindTexture(GL_TEXTURE_2D, texture_glass);
	

	//glColor4f(0, 0, 0, 0.5f);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(0, 8, 0);
		glTexCoord2f(1, 1);
		glVertex3f(5, 8, 0);
		glTexCoord2f(1, 0);
		glVertex3f(5, 0, 0);
	glEnd();

	glPopAttrib();
	GLfloat defaultmtrl[4] = {0, 0, 0, 1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, defaultmtrl);
	glPopMatrix();
}

void smallCorridore() {
	float textures_container[] = { texture_floor, texture_wall, texture_floor };

	int SideSelector[6] = {
		0, // Back
		0, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	float segment[3] = {
		5, 8, 15
	};

	drawCube(segment, SideSelector, textures_container);
}

void largeCorridore() {
	float textures_container[] = { texture_floor, texture_wall, texture_floor };

	float segment[3] = {
		35, 8, 5
	};

	int SideSelector[6] = {
		0, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	drawCube(segment, SideSelector, textures_container);
}

void drawRoof() {
	float frontSide[4][3] = {
			{ 00.0, 0.0, 00.0 },
			{ 35.0, 0.0, 00.0 },
			{ 35.0, 5.0, -17.5 },
			{ 00.0, 5.0, -17.5 }
	};

	float backSide[4][3] = {
			{ 00.0, 0.0, -35.0 },
			{ 35.0, 0.0, -35.0 },
			{ 35.0, 5.0, -17.5 },
			{ 00.0, 5.0, -17.5 }
	};

	glBindTexture(GL_TEXTURE_2D, texture_roof);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(frontSide[0]);

		glTexCoord2f(1.0, 0.0);
		glVertex3fv(frontSide[1]);

		glTexCoord2f(1.0, 1.0);
		glVertex3fv(frontSide[2]);

		glTexCoord2f(0.0, 1.0);
		glVertex3fv(frontSide[3]);
	glEnd();
	glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex3fv(backSide[0]);

		glTexCoord2f(1.0, 0.0);
		glVertex3fv(backSide[1]);

		glTexCoord2f(1.0, 1.0);
		glVertex3fv(backSide[2]);

		glTexCoord2f(0.0, 1.0);
		glVertex3fv(backSide[3]);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_wall);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(frontSide[0]);
		glTexCoord2f(0.5, 0.5);
		glVertex3fv(frontSide[3]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(backSide[0]);
	glEnd();
	glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(frontSide[1]);
		glTexCoord2f(0.5, 0.5);
		glVertex3fv(frontSide[2]);
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(backSide[1]);
	glEnd();
}

void drawHouse() {
	//glPushAttrib(GL_LIGHTING_BIT);
	//addMtrl();

	smallRoom();
	glPushMatrix();
	glTranslatef(15, 0, 0);
	smallCorridore();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 0, 0);
	smallRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -15);
	largeCorridore();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -20);
	largeRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 8, 0);
	drawRoof();
	glPopMatrix();


	glPushMatrix();
	drawWindow();
	glPopMatrix();
}

void rotateDoor(float x, float y, float z)
{
	
	glRotatef(-doorAngle, 0, 1, 0);
	glTranslatef(-x, -y, -z);
	if (isActive)
	{
		
		if (isOpen)
			doorAngle--;
		else
			doorAngle++;
		if (doorAngle == 0)
		{
			isActive = false;
			isOpen = false;
		}
		else if (doorAngle == 90)
		{
			isActive = false;
			isOpen = true;
		}
	}
	glTranslatef(x, y, z);
}
void drawDoor(float x, float y, float z)
{

	glPushMatrix();

	glTranslatef(x, y, z);
	rotateDoor(x, y, z);
	
	glBindTexture(GL_TEXTURE_2D, texture_door);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(5, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(5, 8, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 8, 0);
	glEnd();
	glPopMatrix();
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

void drawSkybox() {
	float fbl[3] = {
		0.0, 0.0, 0.0
	};
	float ftl[3] = {
		0.0, 1000.0, 0.0
	};
	float ftr[3] = {
		1000.0, 1000.0, 0.0
	};
	float fbr[3] = {
		1000.0, 0.0, 0.0
	};
	float bbl[3] = {
		0.0, 0.0, 1000.0
	};
	float btl[3] = {
		0.0, 1000.0, 1000.0
	};
	float btr[3] = {
		1000.0, 1000.0, 1000.0
	};
	float bbr[3] = {
		1000.0, 0.0, 1000.0
	};

	glBindTexture(GL_TEXTURE_2D, texture_sky);

	// front
	glBegin(GL_QUADS);
		glTexCoord2f(0.25, 0.33);
		glVertex3fv(fbl);
		glTexCoord2f(0.25, 0.66);
		glVertex3fv(ftl);
		glTexCoord2f(0.5, 0.66);
		glVertex3fv(ftr);
		glTexCoord2f(0.5, 0.33);
		glVertex3fv(fbr);
	glEnd();

	// back
	glBegin(GL_QUADS);
		glTexCoord2f(0.75, 0.33);
		glVertex3fv(bbr);
		glTexCoord2f(0.75, 0.66);
		glVertex3fv(btr);
		glTexCoord2f(1.0, 0.66);
		glVertex3fv(btl);
		glTexCoord2f(1.0, 0.33);
		glVertex3fv(bbl);
	glEnd();

	// left
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.33);
	glVertex3fv(bbl);
	glTexCoord2f(0.0, 0.66);
	glVertex3fv(btl);
	glTexCoord2f(0.25, 0.66);
	glVertex3fv(ftl);
	glTexCoord2f(0.25, 0.33);
	glVertex3fv(fbl);
	glEnd();

	// right
	glBegin(GL_QUADS);
	glTexCoord2f(0.50, 0.33);
	glVertex3fv(fbr);
	glTexCoord2f(0.50, 0.66);
	glVertex3fv(ftr);
	glTexCoord2f(0.75, 0.66);
	glVertex3fv(btr);
	glTexCoord2f(0.75, 0.33);
	glVertex3fv(bbr);
	glEnd();

	// top
	glBegin(GL_QUADS);
	glTexCoord2f(0.25, 0.66);
	glVertex3fv(ftl);
	glTexCoord2f(0.25, 1.0);
	glVertex3fv(btl);
	glTexCoord2f(0.5, 1.0);
	glVertex3fv(btr);
	glTexCoord2f(0.5, 0.66);
	glVertex3fv(ftr);
	glEnd();

	// bottom
	glBegin(GL_QUADS);
	glTexCoord2f(0.25, 0.0);
	glVertex3fv(bbl);
	glTexCoord2f(0.25, 0.33);
	glVertex3fv(fbl);
	glTexCoord2f(0.50, 0.33);
	glVertex3fv(bbr);
	glTexCoord2f(0.5, 0.0);
	glVertex3fv(bbr);
	glEnd();
}

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

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	
	spotlight();
	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);

	//glDisable(GL_LIGHT0);

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
		isActive = true;
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
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
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
	glEnable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendEquation(GL_FUNC_ADD);
	getimagefromfile("brickwall_2.bmp", &texture_brickwall);
	getimagefromfile("floor.bmp", &texture_floor);
	getimagefromfile("fancy_door.bmp", &texture_door);
	getimagefromfile("grass_3.bmp", &texture_grass);
	getimagefromfile("sky.bmp", &texture_sky);
	getimagefromfile("plaster_texture.bmp", &texture_wall);
	getimagefromfile("glass.bmp", &texture_glass);
	getimagefromfile("roof.bmp", &texture_roof);
	init();

	glutMainLoop();
	return 0;
}

