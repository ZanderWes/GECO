#pragma once

#include <glm.hpp>

class OBB
{
public:

	OBB();
	OBB(float length, float height, float width, 
		glm::fvec3 centerTranslation, glm::fvec3 rotation);

	void setOBB(float length, float height, float width, 
		glm::fvec3 centerTranslation, glm::fvec3 rotation);

	void renderWireframe();

private:
	struct boxFace 
	{
		glm::fvec3 top_left;
		glm::fvec3 top_right;
		glm::fvec3 bottom_left;
		glm::fvec3 bottom_right;
	};

	float lenght_;
	float height_; 
	float width_;
	glm::fvec3 center_point_translation;

	boxFace front_face, back_face;
	

};

