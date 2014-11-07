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
#include <iostream>
#include <glm/glm.hpp>
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

struct LightCoords
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

LightCoords *selectedLight;
LightCoords l1coord;


float teapotAngle = 0.0;

GLfloat normalVectors[6][3] = {
		{ 0, 0, 1 }, // front
		{ 0, 0, -1 }, // back
		{ 1, 0, 0 }, // left
		{ -1, 0, 0 }, // right
		{ 0, 1, 0 }, // top
		{ 0, -1, 0 } // bottom
};

GLfloat ambientMtrl[4] = {
	0.1, 0.1, 0.1, 1.0
};

GLfloat diffuseMtrl[4] = {
	0.43, 0.47, 0.54, 1.0
};

GLuint texture_brickwall;
GLuint texture_floor;
GLuint texture_door;
GLuint texture_grass;
GLuint texture_sky;
GLuint texture_wall;
GLuint texture_glass;
GLuint texture_roof;
GLuint texture_wallpaper;

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

	glColor3fv(white);
	draw_string(30, 20, "Light 1 (Position is relative to house)");
	sprintf_s(buf, "Position:  x: %.2f y: %.2f z: %.2f", l1coord.x, l1coord.y, l1coord.z);
	draw_string(30, 40, buf);

	glPopMatrix();
	resetPerspectiveProjection();
	glEnable(GL_LIGHTING);
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
		l1coord.x, l1coord.y, l1coord.z, l1coord.w
	};
	glutSolidTeapot(1.0);
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
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);

	GLfloat lightColor1[4] = {
		0.1, 0.1, 0.1, 1.0
	};
	GLfloat lightColor2[4] = {
		1.0, 1.0, 1.0, 1.0
	};
	GLfloat lightColor3[4] = {
		1.0, 1.0, 1.0, 1.0
	};
	light1(lightColor1, lightColor2, lightColor3);
	//light2(lightColor1, lightColor2, lightColor3);
	//light3(lightColor1, lightColor2, lightColor3);
}

void disableSpotlight()
{
	glDisable(GL_LIGHT0);
}

void enableSpotlight()
{
	glEnable(GL_LIGHT0);
}

void addTeapot() {
	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);
	glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(8.0, 2.0, -8.0);
		glRotatef(teapotAngle, 0.0, 1.0, 0.0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMtrl);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMtrl);
		glutSolidTeapot(1.0);
	glPopMatrix();
	if (teapotAngle == 360.0)
		teapotAngle = 0.0;
	else
		teapotAngle += 1.0;
	glPopAttrib();
};

void addMtrl() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMtrl);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMtrl);
}

enum Side
{
	front, back, right, left, top, bottom
};

enum WallType
{
	inner, outer
};

glm::vec3 computeNormal(
	glm::vec3 const & a,
	glm::vec3 const & b,
	glm::vec3 const & c, Side side, WallType type)
{
	return glm::normalize(glm::cross(c - a, b - a));
}


void drawQuad_XY(float arr[][3], GLuint texture, GLfloat *normVec, Side side, WallType type) {

	for (float b = arr[0][1]; b < arr[2][1]; b++)	{
		for (float i = arr[0][0]; i < arr[1][0]; i++) {
			glColor3f(1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);
				//
				glm::vec3 av(i, b, 0.0f);
				glm::vec3 bv(i + 1.0f, b, 0.0f);
				glm::vec3 cv(i, b + 1.0f, 0.0f);
				GLfloat t1 = normVec[0];
				GLfloat t2 = normVec[1];
				GLfloat t3 = normVec[2];
				//glm::vec3 normalvec = computeNormal(av, bv, cv, side, type);
				//glNormal3f(normalvec.x, normalvec.y, normalvec.z);
				glNormal3f(t1, t2, t3);
				glTexCoord2f(0, 0);
				glVertex3f(i, b, 0);
				glNormal3fv(normVec);
				glTexCoord2f(1.0, 0);
				glVertex3f(i + 1.0f, b, 0);
				glNormal3fv(normVec);
				glTexCoord2f(1.0, 1.0);
				glVertex3f(i + 1.0f, b + 1.0f, 0);
				glNormal3fv(normVec);
				glTexCoord2f(0, 1.0);
				glVertex3f(i, b + 1.0f, 0);
			glEnd();
		}
	}
}

//void drawCube(float endPoint[3], int sideSelector[6], GLuint *texture_container) {
//
//	float frontbackarr[4][3] = {
//			{ 0.0, 0.0, 0.0 },
//			{ endPoint[0], 0.0, 0.0 },
//			{ 0.0, endPoint[1], 0.0 },
//			{ endPoint[0], endPoint[1], 0.0 }
//	};
//
//	float leftrightarr[4][3] = {
//			{ 0.0, 0.0, 0.0 },
//			{ endPoint[2], 0.0, 0.0 },
//			{ 0.0, endPoint[1], 0.0 },
//			{ endPoint[2], endPoint[1], 0.0 }
//	};
//
//	float roofgroundarr[4][3] = {
//			{ 0.0, 0.0, 0.0 },
//			{ endPoint[0], 0.0, 0.0 },
//			{ 0.0, endPoint[2], 0.0 },
//			{ endPoint[0], endPoint[2], 0.0 }
//	};
//
//	glPushMatrix();
//	if (sideSelector[0] == 1) {
//		glPushMatrix(); // Back
//			glTranslatef(0.0, 0.0, -endPoint[2]);
//			drawQuad_XY(frontbackarr, texture_container[1], normalVectors[1]);
//		glPopMatrix();
//	}
//	if (sideSelector[1] == 1) {
//		glPushMatrix(); // front
//		glTranslatef(0.0, 0.0, 0.0);
//		drawQuad_XY(frontbackarr, texture_container[1], normalVectors[0]);
//		glPopMatrix();
//	}
//	if (sideSelector[2] == 1) {
//		glPushMatrix(); // left
//		glRotatef(90, 0.0, 1.0, 0.0);
//		drawQuad_XY(leftrightarr, texture_container[1], normalVectors[3]);
//		glPopMatrix();
//	}
//	if (sideSelector[3] == 1) {
//		glPushMatrix(); // right
//		glRotatef(90, 0.0, 1.0, 0.0);
//		glTranslatef(0.0, 0.0, endPoint[0]);
//		drawQuad_XY(leftrightarr, texture_container[1], normalVectors[3]);
//		glPopMatrix();
//	}
//	if (sideSelector[4] == 1) {
//		glPushMatrix(); // roof
//		glRotatef(270, 1.0, 0.0, 0.0);
//		glTranslatef(0.0, 0.0, endPoint[1]);
//		drawQuad_XY(roofgroundarr, texture_container[2], normalVectors[4]);
//		glPopMatrix();
//	}
//	if (sideSelector[5] == 1) {
//		glPushMatrix(); // ground
//		glRotatef(270, 1.0, 0.0, 0.0);
//		drawQuad_XY(roofgroundarr, texture_container[0], normalVectors[5]);
//		glPopMatrix();
//	}
//	glPopMatrix();
//
//}
GLfloat normalVectorsOuterWalls[6][3] = {
		{ 0, 0, 1 }, // front
		{ 0, 0, -1 }, // back
		{ 1, 0, 0 }, // left
		{ -1, 0, 0 }, // right
		{ 0, 1, 0 }, // top
		{ 0, -1, 0 } // bottom
};
GLfloat normalVectorsInnerWalls[6][3] = {
		{ 0, 0, -1 }, // front
		{ 0, 0, 1 }, // back
		{ 1, 0, 0 }, // left
		{ -1, 0, 0 }, // right
		{ 0, -1, 0 }, // top
		{ 0, 1, 0 } // bottom
};
void drawCube(float endPoint[3], int sideSelector[6], GLuint *texture_container, bool isOuterWall) {

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
		if (isOuterWall)
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsOuterWalls[1], back, outer);
		else
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsInnerWalls[1], back, inner);
		glPopMatrix();
	}
	if (sideSelector[1] == 1) {
		glPushMatrix(); // front
		glTranslatef(0.0, 0.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsOuterWalls[0], front, outer);
		else
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsInnerWalls[0], front, inner);
		glPopMatrix();
	}
	if (sideSelector[2] == 1) {
		glPushMatrix(); // left
		glRotatef(90, 0.0, 1.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsOuterWalls[0], left, outer);
		else
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsInnerWalls[1], left, inner);
		glPopMatrix();
	}
	if (sideSelector[3] == 1) {
		glPushMatrix(); // right
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[0]);
		if (isOuterWall)
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsOuterWalls[1], right, outer);
		else
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsInnerWalls[0], right, inner);
		glPopMatrix();
	}
	if (sideSelector[4] == 1) {
		glPushMatrix(); // ceiling
		glRotatef(270, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[1]);
		if (isOuterWall)
			drawQuad_XY(roofgroundarr, texture_container[2], normalVectorsOuterWalls[1], top, outer);
		else
			drawQuad_XY(roofgroundarr, texture_container[2], normalVectorsInnerWalls[0], top, inner);
		glPopMatrix();
	}
	if (sideSelector[5] == 1) {
		glPushMatrix(); // ground
		glRotatef(270, 1.0, 0.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(roofgroundarr, texture_container[0], normalVectorsOuterWalls[0], bottom, outer);
		else
			drawQuad_XY(roofgroundarr, texture_container[0], normalVectorsInnerWalls[1], bottom, inner);
		glPopMatrix();
	}
	glPopMatrix();

}

void smallRoom() {
	GLuint textures_container[] = { texture_floor, texture_wallpaper, texture_floor };

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

	drawCube(leftSegment, leftSideSelector, textures_container, false);

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
	drawCube(MiddleSegment, middleSideSelector, textures_container, false);
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
	drawCube(rightSegment, rightSideSelector, textures_container, false);
	glPopMatrix();
}


void leftOuterWall() {
	GLuint textures_container[] = { texture_wall };

	int SideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		0, // right
		0, // roof
		0 // ground
	};
	float Segment[3] = {
		17, 8, 44
	};

	glPushMatrix();
	drawCube(Segment, SideSelector, textures_container, true);
	glPopMatrix();
}

void rightOuterWall() {
	GLuint textures_container[] = { texture_wall };

	int SideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		1, // right
		0, // roof
		0 // ground
	};
	float Segment[3] = {
		17, 8, 44
	};

	glPushMatrix();
	drawCube(Segment, SideSelector, textures_container, true);
	glPopMatrix();
}

void largeRoom() {
	GLuint textures_container[] = { texture_floor, texture_wall, texture_floor };


	int leftSideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		0, // right
		1, // roof
		1 // ground
	};

	float leftSegment[3] = {
		16, 8, 15
	};

	drawCube(leftSegment, leftSideSelector, textures_container, false);

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
	glTranslatef(16, 0, 0);
	drawCube(MiddleSegment, middleSideSelector, textures_container, false);
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
		16, 8, 15
	};

	glPushMatrix();
	glTranslatef(21, 0, 0);
	drawCube(rightSegment, rightSideSelector, textures_container, false);
	glPopMatrix();
}


void drawWindow(GLfloat x, GLfloat y, GLfloat z)
{
	glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	//glTranslatef(17, 0, -44);
	glTranslatef(x, y, z);
	GLfloat windowMtrl[4] = {
		0.0, 0.0, 0.0, 0.5
	};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, windowMtrl);

	glBindTexture(GL_TEXTURE_2D, texture_glass);


	//glColor4f(0, 0, 0, 0.5f);
	glBegin(GL_QUADS);
		glNormal3fv(normalVectors[1]);
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
	GLuint textures_container[] = { texture_floor, texture_wall, texture_floor };

	int SideSelector[6] = {
		0, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	float segment[3] = {
		5, 8, 17
	};

	drawCube(segment, SideSelector, textures_container, false);
}

void largeCorridore() {
	GLuint textures_container[] = { texture_floor, texture_wall, texture_floor };

	float l1segment[3] = {
		5, 8, 10
	};

	int l1SideSelector[6] = {
		1, // Back
		1, // front
		1, // left
		0, // right
		1, // roof
		1 // ground
	};

	drawCube(l1segment, l1SideSelector, textures_container, false);

	float l2segment[3] = {
		5, 8, 10
	};

	int l2SideSelector[6] = {
		1, // Back
		0, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(5, 0, 0);
	drawCube(l2segment, l2SideSelector, textures_container, false);
	glPopMatrix();

	float l2fsegment[3] = {
		5, 8, 1
	};

	int l2fSideSelector[6] = {
		0, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(5, 0, 1);
	drawCube(l2fsegment, l2fSideSelector, textures_container, false);
	glPopMatrix();

	float l3segment[3] = {
		6, 8, 10
	};

	int l3SideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(10, 0, 0);
	drawCube(l3segment, l3SideSelector, textures_container, false);
	glPopMatrix();

	float cSegment[3] = {
		5, 8, 10
	};

	int cSideSelector[6] = {
		0, // Back
		0, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(16, 0, 0);
	drawCube(cSegment, cSideSelector, textures_container, false);
	glPopMatrix();

	float cbSegment[3] = {
		5, 8, 1
	};

	int cbSideSelector[6] = {
		0, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(16, 0, -10);
	drawCube(cbSegment, cbSideSelector, textures_container, false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(16, 0, -26);
	drawCube(cbSegment, cbSideSelector, textures_container, false);
	glPopMatrix();

	float r1segment[3] = {
		6, 8, 10
	};

	int r1SideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(21, 0, 0);
	drawCube(r1segment, r1SideSelector, textures_container, false);
	glPopMatrix();

	float r2Segment[3] = {
		5, 8, 10
	};

	int r2SideSelector[6] = {
		1, // Back
		0, // front
		0, // left
		0, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(27, 0, 0);
	drawCube(r2Segment, r2SideSelector, textures_container, false);
	glPopMatrix();

	float r2fSegment[3] = {
		5, 8, 1
	};

	int r2fSideSelector[6] = {
		0, // Back
		0, // front
		1, // left
		1, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(27, 0, 1);
	drawCube(r2fSegment, r2fSideSelector, textures_container, false);
	glPopMatrix();

	float r3Segment[3] = {
		5, 8, 10
	};

	int r3SideSelector[6] = {
		1, // Back
		1, // front
		0, // left
		1, // right
		1, // roof
		1 // ground
	};

	glPushMatrix();
	glTranslatef(32, 0, 0);
	drawCube(r3Segment, r3SideSelector, textures_container, false);
	glPopMatrix();

}

void drawRoof() {
	float frontSide[4][3] = {
			{ 00.0, 0.0, 00.0 },
			{ 39.0, 0.0, 00.0 },
			{ 39.0, 5.0, -22 },
			{ 00.0, 5.0, -22 }
	};

	float backSide[4][3] = {
			{ 00.0, 0.0, -44.0 },
			{ 39.0, 0.0, -44.0 },
			{ 39.0, 5.0, -22 },
			{ 00.0, 5.0, -22 }
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
	glPushAttrib(GL_LIGHTING_BIT);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMtrl);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMtrl);

	
	leftOuterWall();

	glPushMatrix();
	glTranslatef(22, 0, 0);
	rightOuterWall();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 0, -1);
	smallRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(23, 0, -1);
	smallRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(17, 0, 0);
	smallCorridore();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, -17);
	largeCorridore();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, -28);
	largeRoom();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 8, 0);
	drawRoof();
	glPopMatrix();

	glPushMatrix();
	drawWindow(17, 0, -44);
	drawWindow(17, 0, -43);// glTranslatef(17, 0, -44);
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
		glNormal3fv(normalVectors[1]);
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
	drawDoor(17, 0, 0);
	drawDoor(6, 0, -16);
	drawDoor(28, 0, -16);
	drawDoor(17, 0, -27);
}

void drawGarden() {
	GLuint textures_container[] = { texture_grass, texture_brickwall, texture_floor };

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

	drawCube(leftSegment, leftSideSelector, textures_container, false);
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

	spotlight();

	gluLookAt(	x, 1.0f, z,
				x+lx, 1.0f,  z+lz,
				0.0f, 1.0f,  0.0f);


	//addMtrl();
	//

	glTranslatef(-2, -5, -25);
	
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

	render_info();
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
	case 's':
		disableSpotlight();
		break;
	case 'S':
		enableSpotlight();
		break;
	case 'u':
		selectedLight->x += 0.1;
		break;
	case 'U':
		selectedLight->x -= 0.1;
		break;
	case 'j':
		selectedLight->y += 0.1;
		break;
	case 'J':
		selectedLight->y -= 0.1;
		break;
	case 'm':
		selectedLight->z += 0.1;
		break;
	case 'M':
		selectedLight->z -= 0.1;
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

void light_point_menu(int value) {
	switch (value) {
	case 'a':
		selectedLight = &l1coord;
	case 'b':
		break;
	case 'c':
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

	glutCreateMenu(light_point_menu);
	glutAddMenuEntry("Choose Light:", 0);
	glutAddMenuEntry("Light 1", 'a');
	glutAddMenuEntry("Light 2", 'b');
	glutAddMenuEntry("Light 3", 'c');
	glutAttachMenu(GLUT_RIGHT_BUTTON);


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

void initializeLights()
{
	//Default
	selectedLight = &l1coord;
	//Light 1
	l1coord.x = 8.0;
	l1coord.y = 6;
	l1coord.z = -8.0;
	l1coord.w = 1.0;
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
	glEnable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	getimagefromfile("brickwall_2.bmp", &texture_brickwall);
	getimagefromfile("floor.bmp", &texture_floor);
	getimagefromfile("fancy_door.bmp", &texture_door);
	getimagefromfile("grass_3.bmp", &texture_grass);
	getimagefromfile("sky.bmp", &texture_sky);
	getimagefromfile("plaster_texture.bmp", &texture_wall);
	getimagefromfile("glass.bmp", &texture_glass);
	getimagefromfile("roof.bmp", &texture_roof);
	getimagefromfile("wallpaper.bmp", &texture_wallpaper);
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	//glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	initializeLights();
	init();
	glutMainLoop();
	return 0;
}

