#pragma once

#include "OBB.h"

class RigidBody
{
public:
	RigidBody();
	//RigidBody()

	void setColliderBox();

private:
	OBB collider_box;



};

