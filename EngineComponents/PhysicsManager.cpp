#include "PhysicsManager.h"

void PhysicsManager::Render(q3Render* render)
{
	for (auto var : body_list)
	{
		var.Render(render);
	}
}
