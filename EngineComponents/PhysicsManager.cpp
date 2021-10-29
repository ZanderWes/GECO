#include "PhysicsManager.h"
#include "qu3e/src/dynamics/q3Contact.h"
#include "qu3e/src/math/q3Mat3.h"
#include "qu3e/src/math/q3Transform.h"

void PhysicsManager::Render(q3Renderer* render)
{
	for (auto var : body_list)
	{
		var->Render(render);
	}
}

void PhysicsManager::AddRigidBody(RigidBody* body)
{
	this->body_list.push_back(body);
}


bool PhysicsManager::checkCollision()
{
	for (int i = 0; i < this->body_list.size() - 1; i++)
	{
		for (int k = i + 1; k < this->body_list.size(); k++)
		{
			/*q3Box* box1 = this->body_list[i]->getBoxCollider();
			q3Box* box2 = this->body_list[k]->getBoxCollider();

			q3Manifold* collision_check_pair;
			q3BoxtoBox(collision_check_pair, box1, box2);

			this->collision_data_list.push_back(collision_check_pair);*/
		}
	}
}


PhysicsManager::~PhysicsManager() {

	for (auto body : this->body_list)
	{
		delete body;
		body = nullptr;
	}
	body_list.clear();
}