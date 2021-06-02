#pragma once

#include <iostream>
#include <ios>
#include <fstream>
#include <GL\glut.h>
#include <algorithm>
//#include <SOIL.h>
//#include <SOIL/SOIL.h>

class ImageLoader
{
public:
	void loadImage(const char *filename, int size);

	int getSize();

	inline char getTextureID() { return imageData[0]; };

private:

	unsigned char *imageData;
	int size;

	unsigned char *textureID;
};

