

#pragma once

#include <glm.hpp>
#include "OBB.h"

namespace CollisionDetection
{

	bool checkCollision(OBB &box1, OBB &box2);

	glm::fvec3 collisionPoint(OBB& box1, OBB& box2);

}

