#include "house.h"

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
		5, 8, 15
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
	glNormal3f(0.0, 0.0, 1.0);
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
	GLfloat defaultmtrl[4] = { 0, 0, 0, 1 };
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
	addMaterial();


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
