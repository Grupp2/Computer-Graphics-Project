#include "house.h"

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