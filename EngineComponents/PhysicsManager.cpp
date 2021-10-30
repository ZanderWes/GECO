

#include "PhysicsManager.h"



#include "qu3e/src/dynamics/q3Contact.h"
#include "qu3e/src/math/q3Mat3.h"
#include "qu3e/src/math/q3Transform.h"
#include "qu3e/src/collision/q3Collide.h"
#include "qu3e/src/collision/q3Collide.cpp"

void PhysicsManager::Render(q3Renderer* render)
{
	for (auto var : body_list)
	{
		var->Render(render);
	}
}

void PhysicsManager::Step(double delta_t)
{
	for (auto body : this->body_list)
	{
		body.get()->Update(delta_t);
	}
}

void PhysicsManager::AddRigidBody(std::shared_ptr<RigidBody> body)
{
	this->body_list.push_back(body);
}


void PhysicsManager::checkCollision()
{
	for (int i = 0; i < this->body_list.size() - 1; i++)
	{
		for (int k = i + 1; k < this->body_list.size(); k++)
		{
			//std::shared_ptr<q3Box> box1 = this->body_list[i].get()->getBoxCollider();
			std::shared_ptr<q3Box> box1 = this->body_list[i]->getBoxCollider();
			std::shared_ptr<q3Box> box2 = this->body_list[k]->getBoxCollider();

			std::shared_ptr<q3Manifold> collision_check_pair = std::make_shared<q3Manifold>();
			q3BoxtoBox(collision_check_pair.get(), box1.get(), box2.get());

			if(collision_check_pair.get()->contactCount > 0)
				this->collision_data_list.push_back(collision_check_pair);
		}
	}
}

void PhysicsManager::solve()
{
	if(this->collision_data_list.size() > 0)
		this->collision_data_list.clear();

}

PhysicsManager::~PhysicsManager() {

	/*for (auto body : this->body_list)
	{
		delete body;
		body = nullptr;
	}*/
	body_list.clear();
}

Impulse PhysicsManager::calculateCollisionImpulse(InertiaVector3 J1, InertiaVector3 J2,
	DirectionalVec3 normal, VelocityVec3 V1, VelocityVec3 V2, DirectionalVec3 r1, DirectionalVec3 r2,
	Mass m1, Mass m2, AngularVelocityVec3 w1, AngularVelocityVec3 w2, float Ee) 
{
	/*   Calculating the Numerator   */
	float coefficient = -(1 + Ee);
	float normal_dot_velocities = glm::dot((V1.value - V2.value), normal.value); 
	float angular_dot_distance_normal = glm::dot(w1.value, glm::cross(r1.value, normal.value)) - 
		glm::dot(w2.value, glm::cross(r2.value, normal.value)); 

	float numerator = coefficient * (normal_dot_velocities + angular_dot_distance_normal);

	/*   Calculating the Denominator   */
	float masses = m1.value + m2.value;

	glm::fvec3 normal_r1 = glm::cross(r1.value, normal.value);
	glm::fvec3 J1_mult_rXn = normal_r1 * J1.value;
	float J1_normal_distance = glm::dot(normal_r1, J1_mult_rXn);

	glm::fvec3 normal_r2 = glm::cross(r2.value, normal.value);
	glm::fvec3 J2_mult_rXn = normal_r2 * J2.value;
	float J2_normal_distance = glm::dot(normal_r2, J2_mult_rXn);

	float denominator = masses + (J1_normal_distance + J2_normal_distance);

	/*  Time to put it all together  */
	Impulse impulse;
	impulse.value = numerator / denominator; 

	return impulse;
}