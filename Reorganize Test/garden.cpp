#include "garden.h"


void drawGarden()
{
	GLuint textures_container[] = { texture_grass, texture_brickwall, texture_floor };
	glPushAttrib(GL_LIGHTING_BIT);
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
	addMaterial();
	drawCube(leftSegment, leftSideSelector, textures_container, false);
	glPopAttrib();
}
