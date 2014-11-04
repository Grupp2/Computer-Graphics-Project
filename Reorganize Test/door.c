#include "door.h"

bool isOpen = false;
bool isActive = false;
float doorAngle = 0.0;

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

void setisactive(bool b)
{
	isActive = b;
}
