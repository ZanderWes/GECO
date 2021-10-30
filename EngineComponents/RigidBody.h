#pragma once

#include <memory>

#include "Def_Math_Types_398.h"
#include "qu3e/src/math/q3Math.h"
#include "qu3e/src/math/q3Transform.h"
#include "q3Renderer.h"

class q3Render;
struct q3Box;


class RigidBody
{
public:
	RigidBody();
	RigidBody(Mass mass, Point3D position);
	~RigidBody();

	void Update(float delta_t);

	void setColliderBox();
	void Render(q3Renderer* render) const;
	
	std::shared_ptr<q3Box> getBoxCollider();

	InertiaVector3 getMomentOfInertia();
	Point3D getBodyCentreofMass();

	void setLinearVelocity(VelocityVec3 linear_vel);
	VelocityVec3 getLinearVelocity();

	void setAngularVelocity(AngularVelocityVec3 angular_vel);
	AngularVelocityVec3 getAngularVelocity();

private:

	std::shared_ptr<q3Box> collider_box = nullptr;
	float mass;

	VelocityVec3 linear_velocity;
	AngularVelocityVec3 angular_velocity;

	void applyMovement(float delta_t);
};

