#include "textures.h"

GLuint texture_brickwall = 0;
GLuint texture_floor = 0;
GLuint texture_door = 0;
GLuint texture_grass = 0;
GLuint texture_sky = 0;
GLuint texture_wall = 0;
GLuint texture_glass = 0;
GLuint texture_roof = 0;
GLuint texture_wallpaper = 0;


void getimagefromfile(const char *src, GLuint *texname)
{
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

void loadTextures()
{
	getimagefromfile("brickwall_2.bmp", &texture_brickwall);
	getimagefromfile("floor.bmp", &texture_floor);
	getimagefromfile("fancy_door.bmp", &texture_door);
	getimagefromfile("grass_3.bmp", &texture_grass);
	getimagefromfile("sky.bmp", &texture_sky);
	getimagefromfile("plaster_texture.bmp", &texture_wall);
	getimagefromfile("glass.bmp", &texture_glass);
	getimagefromfile("roof.bmp", &texture_roof);
	getimagefromfile("wallpaper.bmp", &texture_wallpaper);
}

