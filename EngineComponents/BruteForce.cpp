/*#include "BruteForce.h"

void BruteForce::render()
{
	unsigned char hcolor;

	for (int z = 0; z < getSize() - 1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		
		for (int x = 0; x < getSize(); x++) {
			
			hcolor = getHeightColor(x, z);
			glColor3ub(hcolor, hcolor, hcolor);
			glVertex3f((float)x * scaleX, getHeight(x, z), (float)z * scaleZ);
			
			hcolor = getHeightColor(x, z + 1);
			glColor3ub(hcolor, hcolor, hcolor);
			glVertex3f((float)x * scaleX, getHeight(x, z + 1), (float)(z + 1) * scaleZ);
		}
		glEnd();
	}
}*/
