#pragma once

#include <iostream>
#include <ios>
#include <fstream>
#include <GL\glut.h>



class Terrain
{
public:

	bool loadHeightfield(const char* filename, int size);

	void loadHeightfieldTexture(const char* filename, int size);

	void generateFractalHeightfield(int size);

	void setScalingFactor(float xScale, float yScale, float zScale);

	inline int getSize() { return size; }

	float getSurfaceHeight(int x, int z);
	
	unsigned char getHeightColor(int x, int z);

	float getHeight(int x, int y);

	void addFilter(unsigned char* terrainData, float weight);

	void filterPass(unsigned char* startP, int increment, float weight);

	void normaliseTerrain();

protected:

	unsigned char* terrainData;
	float scaleX;
	float scaleY;
	float scaleZ;

	//ImageLoader texture;
	GLuint texture;

private:
	int size;

	bool inbounds(int x, int z);
};

class BruteForce : public Terrain
{
public:

	void render();

};

class Fractal : public Terrain
{
public:

	void render();
};