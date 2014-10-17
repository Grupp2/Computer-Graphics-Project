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

/*
// Include GLM core features
#include "Labb_2_parametric_Curves_Hermite\Labb2\glm\glm\vec3.hpp"
#include "Labb_2_parametric_Curves_Hermite\Labb2\glm\glm\vec4.hpp"
#include "Labb_2_parametric_Curves_Hermite\Labb2\glm\glm\mat4x4.hpp"

// Include GLM extensions
#include "Labb_2_parametric_Curves_Hermite\Labb2\glm\glm\gtc\matrix_transform.hpp"
*/

// The position of the origin of the scene:
float x_pos = 0.0;
float y_pos = 0.0;
float z_pos = -6.5;

float theta = 0.0;
float phi = 0.0;

float alpha = 0.0;
float angle_delta = 0.5;

// The previous mouse position:
int x_prev = 0;
int y_prev = 0;

int w = 800;
int h = 600;

GLfloat colors[3][3] = { { 1.0, 0.0, 0.0 },
{ 0.0, 1.0, 0.0 },
{ 1.0, 1.0, 0.0 } };

// Positions of vertices for the coordinate system:
float coords[6][3] = { { -2.0, 0.0, 0.0 },
{ 2.0, 0.0, 0.0 },
{ 0.0, -2.0, 0.0 },
{ 0.0, 2.0, 0.0 },
{ 0.0, 0.0, -2.0 },
{ 0.0, 0.0, 2.0 } };

GLfloat ctrl_point_pos[4][3] = { { -2.0, 0.0, 0.0 },
{ -1.0, 0.0, 0.0 },
{ 1.0, 0.0, 0.0 },
{ 2.0, 0.0, 0.0 } };

enum ctrl_points { P0, P1, P2, P3 };

GLfloat ctrlpoints[4][3] = {
		{ -4.0, -4.0, 0.0 },
		{ -2.0, 4.0, 0.0 },
		{ 2.0, -4.0, 0.0 },
		{ 4.0, 4.0, 0.0 }
};

GLfloat dp_points[2][3] = {
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }
};

int ctrlp = P0;

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

void draw_string(float x, float y, char *string)
{
	//char *s;
	int i = 0;

	glRasterPos2f(x, y);
	while (string[i] != '\0')
	{
		glutBitmapCharacter(font_style, string[i]);
		i++;
	}
}

void render_info()
{
	float green[] = { 0.0, 1.0, 0.0 };
	float white[] = { 1.0, 1.0, 1.0 };

	float *p0_col = white;
	float *p1_col = white;
	float *p2_col = white;
	float *p3_col = white;

	if (ctrlp == P0)
		p0_col = green;
	else if (ctrlp == P1)
		p1_col = green;
	else if (ctrlp == P2)
		p2_col = green;
	else if (ctrlp == P3)
		p3_col = green;

	glDisable(GL_LIGHTING);
	setfont("8x13", 20);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();

	glColor3fv(white);
	draw_string(30, 20, "Control Points");
	sprintf(buf, "P0:   %.2f:%.2f:%.2f", ctrl_point_pos[0][0], ctrl_point_pos[0][1], ctrl_point_pos[0][2]);
	glColor3fv(p0_col);
	draw_string(30, 40, buf);
	sprintf(buf, "P1:   %.2f:%.2f:%.2f", ctrl_point_pos[1][0], ctrl_point_pos[1][1], ctrl_point_pos[1][2]);
	glColor3fv(p1_col);
	draw_string(30, 60, buf);
	sprintf(buf, "P2:   %.2f:%.2f:%.2f", ctrl_point_pos[2][0], ctrl_point_pos[2][1], ctrl_point_pos[2][2]);
	glColor3fv(p2_col);
	draw_string(30, 80, buf);
	sprintf(buf, "P3:   %.2f:%.2f:%.2f", ctrl_point_pos[3][0], ctrl_point_pos[3][1], ctrl_point_pos[3][2]);
	glColor3fv(p3_col);
	draw_string(30, 100, buf);

	glPopMatrix();
	resetPerspectiveProjection();
}

void do_idle()
{
	glutPostRedisplay();
}

void reshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(55.0, (double)(width) / (double)(height), 0.1, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(x_pos, y_pos, z_pos);

	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'x':
		// decrease x-component of active control point
		(ctrlpoints[ctrlp][0]) -= 0.1;
		break;
	case 'X':
		// increase x-component of active control point
		(ctrlpoints[ctrlp][0]) += 0.1;
		break;
	case 'y':
		// decrease y-component of active control point
		(ctrlpoints[ctrlp][1]) -= 0.1;
		break;
	case 'Y':
		// increase y-component of active control point
		(ctrlpoints[ctrlp][1]) += 0.1;
		break;
	case 'z':
		// decrease z-component of active control point
		(ctrlpoints[ctrlp][2]) -= 0.1;
		break;
	case 'Z':
		// increase z-component of active control point
		(ctrlpoints[ctrlp][2]) += 0.1;
		break;
	default:
		// do nothing...
		break;
	}
}

void special_buttons(int key, int x, int y) {
	float step = 0.1;

	switch (key) {
	case GLUT_KEY_RIGHT:
		x_pos -= step;
		break;
	case GLUT_KEY_LEFT:
		x_pos += step;
		break;
	case GLUT_KEY_UP:
		z_pos += step;
		break;
	case GLUT_KEY_DOWN:
		z_pos -= step;
		break;
	case 104:
		y_pos -= step;
		break;
	case 105:
		y_pos += step;
		break;
	default:
		// do nothing...
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
		ctrlp = P0;
		break;
	case 'b':
		ctrlp = P1;
		break;
	case 'c':
		ctrlp = P2;
		break;
	case 'd':
		ctrlp = P3;
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


}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer Graphics, Project");

	init();

	glutMainLoop();
	return 0;
}

