#include "RigidBody.h"


void RigidBody::Render(q3Render* render) const
{
	this->collider_box->Render(render);
}