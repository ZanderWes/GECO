#pragma once

#include <vector>
#include <memory>

#include "RigidBody.h"
#include "qu3e/src/collision/q3Collide.h"
#include "qu3e/src/dynamics/q3Contact.h"
#include "Def_Math_Types_398.h"
#include "qu3e/src/math/q3Transform.h"

//class q3Transform;

class PhysicsManager
{
public:

	void Render(q3Renderer* render);
	void Step(double delta_t);
	void AddRigidBody(std::shared_ptr<RigidBody> body);

	~PhysicsManager();

private:
	struct CollisionPair
	{
		std::shared_ptr<q3Manifold> collision_data;
		std::shared_ptr<RigidBody> body1;
		std::shared_ptr<RigidBody> body2;
	};


	void checkCollision();
	void solve();

	std::vector<std::shared_ptr<RigidBody>> body_list;

	Impulse calculateCollisionImpulse(InertiaVector3 J1, InertiaVector3 J2,	DirectionalVec3 normal, 
		VelocityVec3 V1, VelocityVec3 V2, DirectionalVec3 r1, DirectionalVec3 r2,
		Mass m1, Mass m2, AngularVelocityVec3 w1, AngularVelocityVec3 w2, float Ee);

	std::vector<std::shared_ptr<q3Manifold>> collision_data_list;
	std::vector<CollisionPair> collision_pair_list;

	//RigidBody rigidbody;

};

