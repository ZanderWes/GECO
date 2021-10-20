#pragma once

#include "Def_Math_Types_398.h"
#include "qu3e/src/math/q3Mat3.h"
#include "qu3e/src/math/q3Transform.h"

class q3Render;
struct q3Box;

class RigidBody
{
public:
	RigidBody() {}
	RigidBody(Mass mass, Point3D position);

	void setColliderBox();
	void Render(q3Render* render) const;
	

private:

	q3Box *collider_box = nullptr;
	//OBB collider_box;



};

