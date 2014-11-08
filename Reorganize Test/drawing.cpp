#include "drawing.h"

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



void drawQuad_XY(float arr[][3], GLuint texture, GLfloat *normVec) {

	for (float b = arr[0][1]; b < arr[2][1]; b++)	{
		for (float i = arr[0][0]; i < arr[1][0]; i++) {
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);

			GLfloat t1 = normVec[0];
			GLfloat t2 = normVec[1];
			GLfloat t3 = normVec[2];
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
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsOuterWalls[1]);
		else
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsInnerWalls[1]);
		glPopMatrix();
	}
	if (sideSelector[1] == 1) {
		glPushMatrix(); // front
		glTranslatef(0.0, 0.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsOuterWalls[0]);
		else
			drawQuad_XY(frontbackarr, texture_container[1], normalVectorsInnerWalls[0]);
		glPopMatrix();
	}
	if (sideSelector[2] == 1) {
		glPushMatrix(); // left
		glRotatef(90, 0.0, 1.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsOuterWalls[0]);
		else
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsInnerWalls[1]);
		glPopMatrix();
	}
	if (sideSelector[3] == 1) {
		glPushMatrix(); // right
		glRotatef(90, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[0]);
		if (isOuterWall)
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsOuterWalls[1]);
		else
			drawQuad_XY(leftrightarr, texture_container[1], normalVectorsInnerWalls[0]);
		glPopMatrix();
	}
	if (sideSelector[4] == 1) {
		glPushMatrix(); // ceiling
		glRotatef(270, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, endPoint[1]);
		if (isOuterWall)
			drawQuad_XY(roofgroundarr, texture_container[2], normalVectorsOuterWalls[1]);
		else
			drawQuad_XY(roofgroundarr, texture_container[2], normalVectorsInnerWalls[0]);
		glPopMatrix();
	}
	if (sideSelector[5] == 1) {
		glPushMatrix(); // ground
		glRotatef(270, 1.0, 0.0, 0.0);
		if (isOuterWall)
			drawQuad_XY(roofgroundarr, texture_container[0], normalVectorsOuterWalls[0]);
		else
			drawQuad_XY(roofgroundarr, texture_container[0], normalVectorsInnerWalls[1]);
		glPopMatrix();
	}
	glPopMatrix();

}
