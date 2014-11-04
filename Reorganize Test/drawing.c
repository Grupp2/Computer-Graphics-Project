#include "drawing.h"

GLfloat normalVectors[6][3] = {
		{ 0, 0, 1 }, // front
		{ 0, 0,-1 }, // back
		{ 1, 0, 0 }, // left
		{-1, 0, 0 }, // right
		{ 0, 1, 0 }, // top
		{ 0, -1, 0 } // bottom
};

void drawQuad_XY(float arr[][3], GLuint texture, GLfloat *normVec) {

	for (int b = arr[0][1]; b < arr[2][1]; b++)	{
		for (int i = arr[0][0]; i < arr[1][0]; i++) {
			glColor3f(1, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);
				glNormal3fv(normVec);
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
			drawQuad_XY(frontbackarr, texture_container[1], normalVectors[0]);
		glPopMatrix();
	}
	if (sideSelector[1] == 1) {
		glPushMatrix(); // front
		glTranslatef(0.0, 0.0, 0.0);
		drawQuad_XY(frontbackarr, texture_container[1], normalVectors[1]);
		glPopMatrix();
	}
	if (sideSelector[2] == 1) {
		glPushMatrix(); // left
		glRotatef(90, 0.0, 1.0, 0.0);
		drawQuad_XY(leftrightarr, texture_container[1], normalVectors[2]);
		glPopMatrix();
	}
	if (sideSelector[3] == 1) {
		glPushMatrix(); // right
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[0]);
		drawQuad_XY(leftrightarr, texture_container[1], normalVectors[3]);
		glPopMatrix();
	}
	if (sideSelector[4] == 1) {
		glPushMatrix(); // roof
		glRotatef(270, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[1]);
		drawQuad_XY(roofgroundarr, texture_container[2], normalVectors[4]);
		glPopMatrix();
	}
	if (sideSelector[5] == 1) {
		glPushMatrix(); // ground
		glRotatef(270, 1.0, 0.0, 0.0);
		drawQuad_XY(roofgroundarr, texture_container[0], normalVectors[5]);
		glPopMatrix();
	}
	glPopMatrix();

}

