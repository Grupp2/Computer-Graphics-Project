#include "skybox.h"

void drawSkybox()
{
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
