#pragma once

#include "RigidBody.h"

class PhysicsManager
{
public:


	void Step(double delta_t);

private:

	bool checkCollision();

	RigidBody rigidbody;

};

