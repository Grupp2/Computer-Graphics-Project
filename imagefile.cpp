/*
 *  Computer Graphics
 *
 *  imagefile.cpp
 *
 *  Peter Jenke, Peter.Jenke@hig.se
 *
 *  Version 2013-09-26
 */

#include "imagefile.h"
#include "exceptioninfo.h"
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <FreeImage.h>

using namespace std;

/*
	Reads the data from an image file (defined by the parameter path)
	and returns the name of the texture. The parameter flag is used
	for informing the image loader about some special properties
	of the iamge file.

	Currently, it can only process bitmap files with a bpp of 24 or 32 bits.

	In case of errors, it throws an exception.

	You have to decide which byte order the program uses (depends on the architecture
	of your computer), because the FreeImage library reflects this in the order of the
	data which it extracts from the image file.
	On an x86-system, the byte order is little endian. If you use this program
	on another platform, please change the definition for the byte order
	in the file imagefile.h.

	The order of the color bytes in the data-array is always RGB(A).
*/
ImageFile::ImageFile(const char *path, int flag)
{
	FreeImage_Initialise(FALSE);

	FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
	format = FreeImage_GetFileType(path, 0);

	if (format == FIF_UNKNOWN)
	{
		string msg ("Unknown image format!");
		ExceptionInfo ei (msg, 1);
		throw ei;
	}

	FIBITMAP *image = FreeImage_Load(format, path, flag);

	if (!image)
	{
		string msg ("No image loaded!");
		ExceptionInfo ei (msg, 2);
		throw ei;
	}

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(image);
	if (image_type != FIT_BITMAP)
	{
		string msg ("The image is not a bitmap image!");
		ExceptionInfo ei (msg, 3);
		throw ei;
	}

	imgBPP = FreeImage_GetBPP(image);
	if (imgBPP != 24 &&  imgBPP != 32)
	{
		string msg ("Can only process images with BPP of 24 or 32!");
		ExceptionInfo ei (msg, 4);
		throw ei;
	}

	width = FreeImage_GetWidth(image);
	height = FreeImage_GetHeight(image);
	unsigned int x = 0;
	unsigned int data_pos = 0;
	unsigned int len = 0;

	if(imgBPP == 24) {
		len = 3 * width * height;
		data = new char[len];
		BYTE *bits = (BYTE*)FreeImage_GetBits(image);
		for(x = 0; x < len - 2; x += 3)
		{
		#if defined(LITTLE_ENDIAN_ORDER)
			data[data_pos] = bits[x + 2]; // R
			data[data_pos + 1] = bits[x + 1]; // G
			data[data_pos + 2] = bits[x]; // B
		#elif defined(BIG_ENDIAN_ORDER)
			data[data_pos] = bits[x]; // R
			data[data_pos + 1] = bits[x + 1]; // G
			data[data_pos + 2] = bits[x + 2]; // B
		#endif
			data_pos += 3;
		}
	} else if(imgBPP == 32) {
		len = 4 * width * height;
		data = new char[len];
		BYTE *bits = (BYTE*)FreeImage_GetBits(image);
		for(x = 0; x < len - 3; x += 4)
		{
		#if defined(LITTLE_ENDIAN_ORDER)
			data[data_pos] = bits[x + 2]; // R
			data[data_pos + 1] = bits[x + 1]; // G
			data[data_pos + 2] = bits[x]; // B
		#elif defined(BIG_ENDIAN_ORDER)
			data[data_pos] = bits[x]; // R
			data[data_pos + 1] = bits[x + 1]; // G
			data[data_pos + 2] = bits[x + 2]; // B
		#endif
			data[data_pos + 3] = bits[x + 3]; // A
			data_pos += 4;
		}
	}

	FreeImage_Unload(image);
	FreeImage_DeInitialise();
}

/*
	Returns the width of the image.
*/
int ImageFile::getWidth (void) const
{
	return width;
}

/*
	Returns the height of the image.
*/
int ImageFile::getHeight (void) const
{
	return height;
}

/*
	Returns the bpp of the image.
*/
int ImageFile::getBPP (void) const
{
	return imgBPP;
}

/*
	Returns a pointer at the data of the image.
*/
char* ImageFile::getData () const
{
	return data;
}

ImageFile::~ImageFile (void)
{
	delete data;
}
