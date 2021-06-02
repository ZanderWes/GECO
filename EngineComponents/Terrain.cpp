#include "Terrain.h"
#include <SOIL.h>
//#include <SOIL.h>


bool Terrain::loadHeightfield(const char* filename, int size)
{
	std::ifstream infile(filename, std::ios::in | std::ios::binary);

	if (!infile)
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	if (terrainData)
		delete[] terrainData;

	if (size > 0)
		terrainData = new unsigned char[size * size];

	if (terrainData == NULL)
		return false;

	infile.seekg(0, std::ios::end);
	int length = infile.tellg();

	infile.seekg(0, std::ios::beg);
	infile.read(reinterpret_cast<char*>(terrainData), length);
	infile.close();

	this->size = size;

	return true;
}

void Terrain::loadHeightfieldTexture(const char* filename, int size)
{
	texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//texture.loadImage(filename, size);
	//return true;
}

void Terrain::generateFractalHeightfield(int size)
{

	this->terrainData = new unsigned char[size * size];
	float x1, x2, z1, z2;

	
	unsigned char ch;
	x1 = (rand() % size);
	z1 = (rand() % size);

	do {
		x2 = (rand() % size);
		z2 = (rand() % size);
	} while (x2 == x1 && z2 == z1);
	{
		for (int z = 0; z < size; z++)
		{
			for (int x = 0; x < size; x++)
			{
				this->terrainData[(z * size) + x] = 0;
				int y = (x2 - x1) * (z - z1) - (z2 - z1) * (x - x1);
				if (y > 0)
					this->terrainData[(z * size) + x] += (float)y;
			}
		}
	}
	addFilter(terrainData, 2);

}

void Terrain::setScalingFactor(float xScale, float yScale, float zScale)
{
	this->scaleX = xScale;
	this->scaleY = yScale;
	this->scaleZ = zScale;
}

unsigned char Terrain::getHeightColor(int x, int z)
{
	if (inbounds(x, z))
	{
		return terrainData[z * size + x];
	}
	return 1;
}

float Terrain::getSurfaceHeight(int x, int z)
{
	if (x > 0 && x < size * scaleX && z > 0 && z < size * scaleZ)
	{
		int tempz = z / scaleZ;
		int tempx = x / scaleX;
		return((float)(terrainData[tempz * size + tempx]) * scaleY);
	}
	return 0;
}

float Terrain::getHeight(int xpos, int zpos)
{
		return ((float)(terrainData[(zpos * size) + xpos]) * scaleY);
}

bool Terrain::inbounds(int x, int z)
{
	if (x >= 0 && x < 128 && z >= 0 && z < 128 )
	{
		return true;
	}

	return false;
}


void BruteForce::render()
{
	unsigned int hcolor;
	float specfloat = 0;
	float texLeft, texBottom, texTop;
	//char textimg = texture.getTextureID();

	glEnable(GL_TEXTURE_2D);
	//glGenTextures(1, );
	glBindTexture(GL_TEXTURE_2D, texture);

	for (int z = 0; z < getSize()-1; z++)
	{
		
		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x < getSize()-1; x++) {

			texLeft = (float)z / getSize();
			texBottom = (float)x /getSize();
			texTop = (float)(x + 1) / getSize();

			hcolor = getHeightColor(x, z);
			
			//glColor3ub(hcolor, hcolor , hcolor);
			glTexCoord2f(texLeft, texBottom);
			glVertex3f((float)x * scaleX, getHeight(x, z), (float)z * scaleZ);
			

			hcolor = getHeightColor(x, z + 1);

			//glColor3ub(hcolor * specfloat, hcolor, hcolor * specfloat);
			glTexCoord2f(texLeft, texBottom);
			glVertex3f((float)x * scaleX, getHeight(x, z + 1), (float)(z + 1) * scaleZ);
			
		}
		glEnd();
	}
}

void Terrain::filterPass(unsigned char* startP, int increment, float weight) {
	float yprev = *startP; // the starting point in the terrain array
	int j = increment; // must be either +1, -1, +size, or -size
	float k = weight;
	
	for (int i = 1; i < size; i++) 
	{
		*(startP + j) = k * yprev + (1 - k) * (*(startP + j));
		yprev = *(startP + j);
		j += increment;
	}
}

void Terrain::addFilter(unsigned char* terrainData, float weight) {
	int i;
	//erode left to right, starting from the beginning of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * i], 1, weight);
	//erode right to left, starting from the end of each row
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * i + size - 1], -1, weight);
	//erode top to bottom, starting from the beginning of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[i], size, weight);
	//erode from bottom to top, starting from the end of each column
	for (i = 0; i < size; i++)
		filterPass(&terrainData[size * (size - 1) + i], -size, weight);
}

void Terrain::normaliseTerrain() {
	float fMin = this->terrainData[0];
	float fMax = this->terrainData[0];
	float fHeight;
	int i;
	//find the min and max values of the height terrainData
	for (i = 1; i < size * size; i++) {
		if (terrainData[i] > fMax)
			fMax = terrainData[i];
		else if (terrainData[i] < fMin)
			fMin = terrainData[i];
	}
	//find the range of the altitude
	if (fMax <= fMin)
		return;
	fHeight = fMax - fMin;
	//scale the values to a range of 0-255 
	for (i = 0; i < size * size; i++)
		terrainData[i] = ((terrainData[i] - fMin) / fHeight) * 255.0f;
}

void Fractal::render()
{
	unsigned int hcolor;

	for (int z = 0; z < getSize() - 1; z++)
	{

		glBegin(GL_TRIANGLE_STRIP);

		for (int x = 0; x < getSize() - 1; x++) {

			hcolor = getHeightColor(x, z);

			glColor3ub(hcolor, hcolor, hcolor);
			//glColor3f(0.3, 0.3, 0.3);
			glVertex3f((float)x * scaleX, getHeight(x, z), (float)z * scaleZ);


			hcolor = getHeightColor(x, z + 1);
			glColor3ub(hcolor, hcolor, hcolor);
			//glColor3f(0, 1, 0);
			glVertex3f((float)x * scaleX, getHeight(x, z + 1), (float)(z + 1) * scaleZ);

		}
		glEnd();
	}
}