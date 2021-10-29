#pragma once

#include <vector>
#include "RigidBody.h"
#include "qu3e/src/collision/q3Collide.h"
#include "qu3e/src/dynamics/q3Contact.h"

class PhysicsManager
{
public:

	void Render(q3Renderer* render);
	void Step(double delta_t);
	void AddRigidBody(RigidBody *body);

	~PhysicsManager();

private:

	bool checkCollision();

	std::vector<RigidBody*> body_list;
	//std::vector<q3Manifold*> collision_data_list;

	//RigidBody rigidbody;

};

