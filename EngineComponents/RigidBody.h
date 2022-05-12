#pragma once

#include <memory>

#include "Def_Math_Types_398.h"
#include "Dependancies/qu3e/qu3e/src/math/q3Math.h"
#include "Dependancies/qu3e/qu3e/src/math/q3Transform.h"
#include "q3Renderer.h"
#include "gtc/matrix_transform.hpp"
#include "gtx/quaternion.hpp"


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
	InertiaVector3 getInverseInertiaTensor();

	Point3D getBodyCentreofMass();
	void setBodyPosition(Point3D position);

	void setLinearVelocity(VelocityVec3 linear_vel);
	VelocityVec3 getLinearVelocity();

	void setAngularVelocity(AngularVelocityVec3 angular_vel);
	AngularVelocityVec3 getAngularVelocity();

	void setMass(Mass mass_);
	Mass getMass();

	void setRestitution(float c_o_r);
	float getRestitution();

	void setRotationVector(glm::fvec3 rotate_around);

private:

	std::shared_ptr<q3Box> collider_box = nullptr;
	Mass mass;
	float coefficient_of_restitution = 1;

	VelocityVec3 linear_velocity;
	AngularVelocityVec3 angular_velocity;

	Point3D updated_position;

	glm::fvec3 impulse_rotation_vector;
	//q3Quaternion body_quaternion_rotation;

	void applyMovement(float delta_t);
};

