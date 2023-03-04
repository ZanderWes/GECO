#pragma once

#include <ios>
#include <vector>
#include "SphereCollider.h"
#include "OBB.h"

using namespace std;


struct CollisionData
{
	glm::fvec3 collision_point;
	glm::fvec3 collision_normal;

};

class CollisionManager
{
public:

	//ColliderType getColliderType();

private:
	
	// Lets not get ahead of ourselves yet
	//vector<shared_ptr<OBB>> box_collider_list; 

};


