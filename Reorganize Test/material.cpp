#include "material.h"

GLfloat ambientMtrl[4] = {
	0.1, 0.1, 0.1, 1.0
};

GLfloat diffuseMtrl[4] = {
	0.43, 0.47, 0.54, 1.0
};

void addMaterial() 
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMtrl);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMtrl);
}
