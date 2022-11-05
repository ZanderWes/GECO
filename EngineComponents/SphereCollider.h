
#pragma once

#include <glm.hpp>
#include <gtx/rotate_vector.hpp>


class SphereCollider  
{
public:

	SphereCollider();
	~SphereCollider();


private:

	double radius;
	glm::dvec3 position;

};

