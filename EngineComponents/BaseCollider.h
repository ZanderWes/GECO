#pragma once

#include <ios>
#include "SphereCollider.h"
#include "OBB.h"

/**
* Hopefully one day i will be able to do some inheritance magic...
* Till then this is just taking up precious space
*/

class BaseCollider
{
public:

	BaseCollider();
	~BaseCollider();

	ColliderType getColliderType();

private:

	std::unique_ptr<ColliderType> collider_type = nullptr;
	std::shared_ptr<SphereCollider> sphere_collider = nullptr;
	std::shared_ptr<OBB> box_collider = nullptr;

};


enum ColliderType 
{
	NULL_COLLIDER,
	SPHERE_COLLIDER,
	BOX_COLLIDER
};

