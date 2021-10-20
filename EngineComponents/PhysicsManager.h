#pragma once

#include <vector>
#include "RigidBody.h"

class PhysicsManager
{
public:

	void Render(q3Render* render);
	void Step(double delta_t);

private:

	bool checkCollision();

	std::vector<RigidBody> body_list;

	//RigidBody rigidbody;

};

