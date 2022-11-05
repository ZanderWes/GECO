#pragma once

#include <ios>
#include <vector>
#include "SphereCollider.h"
#include "OBB.h"

using namespace std;

class ColliderManager
{
public:

	//ColliderType getColliderType();

private:

	vector<shared_ptr<SphereCollider>> sphere_collider_list;
	
	// Lets not get ahead of ourselves yet
	//vector<shared_ptr<OBB>> box_collider_list; 

};


