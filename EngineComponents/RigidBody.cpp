#include "RigidBody.h"
#include "qu3e/src/math/q3Mat3.cpp"
#include "qu3e/src/collision/q3Box.cpp"
#include "qu3e/src/broadphase/q3BroadPhase.h"
#include "qu3e/src/dynamics/q3Contact.h"
//#include "qu3e/src/"
#include "qu3e/src/math/q3Vec3.cpp"
//#include "qu3e/src/collision/q3Box.h"



RigidBody::RigidBody()
{
	q3AABB aabb;
	q3Box* box = new q3Box;
	q3Transform transform;
	//transform.position = q3Vec3(0, 0, 0);
	//transform.rotation = q3Mat3(1, 1, 1, 1, 1, 1, 1, 1, 1);

	q3Identity(transform);

	//transform.position += q3Vec3(0, 0, 50);

	box->local = transform;
	box->e = q3Vec3(1, 1, 1);
	box->next = nullptr;
	box->body = nullptr;
	box->friction = 0;
	box->ComputeAABB(transform, &aabb);

	this->mass = 1;

	this->collider_box = box;


	//this->collider_box->local.position = q3Vec3(1, 1, 1);
}

void RigidBody::Render(q3Renderer* render) const
{
	this->collider_box->Render(this->collider_box->local, true, render);
}

q3Box* RigidBody::getBoxCollider()
{
	return this->collider_box; 
}

Point3D RigidBody::getBodyCentreofMass()
{
	
}

InertiaVector3 RigidBody::getMomentOfInertia()
{
	auto extents = this->collider_box->e;

	auto b = extents[0];
	auto a = extents[1];
	auto l = extents[2];

	float Ixx = (1.0 / 12.0) * this->mass * (a * a + l * l);
	float Iyy = (1.0 / 12.0) * this->mass * (b * b + l * l);
	float Izz = (1.0 / 12.0) * this->mass * (a * a + b * b);

	return InertiaVector3(Ixx, Iyy, Izz);
}


RigidBody::~RigidBody()
{
	delete this->collider_box;
	this->collider_box = nullptr;
}