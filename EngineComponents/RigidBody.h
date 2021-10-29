#pragma once

#include "Def_Math_Types_398.h"
#include "qu3e/src/math/q3Math.h"
//#include "qu3e/src/math/q3Mat3.h"
#include "qu3e/src/math/q3Transform.h"
#include "q3Renderer.h"
//#include "qu3e/src/math/q3Vec3.h"
//#include "qu3e/src/"
//#include "qu3e/src/common"

class q3Render;
struct q3Box;


class RigidBody
{
public:
	RigidBody();
	RigidBody(Mass mass, Point3D position);
	~RigidBody();

	void setColliderBox();
	void Render(q3Renderer* render) const;
	
	q3Box* getBoxCollider(); 

	InertiaVector3 getMomentOfInertia();
	Point3D getBodyCentreofMass();

private:

	q3Box *collider_box = nullptr;

	float mass;
	//OBB collider_box;



};

