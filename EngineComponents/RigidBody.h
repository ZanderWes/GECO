#pragma once

#include "OBB.h"
//#include "box.h"
//#include "qu3e/src/q3.h"
#include "qu3e/src/math/q3Mat3.h"
#include "qu3e/src/math/q3Transform.h"

class q3Render;
struct q3Box;

class RigidBody
{
public:
	RigidBody() {}
	//RigidBody()

	void setColliderBox();
	void Render(q3Render* render) const;
	

private:

	q3Box *collider_box = nullptr;
	//OBB collider_box;



};

