/*
 *  Computer Graphics
 *
 *  imagefile.cpp
 *
 *  Peter Jenke, Peter.Jenke@hig.se
 *
 *  Version 2013-09-26
 */

#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#define LITTLE_ENDIAN_ORDER

class ImageFile
{
public:
	ImageFile(const char *path, int flag);
	char* getData () const;
	int getWidth (void) const;
	int getHeight (void) const;
	int getBPP (void) const;
	~ImageFile (void);
private:
	unsigned int imgBPP;
	unsigned long width;
	unsigned long height;
	char *data;
};

#endif // IMAGEFILE_H
