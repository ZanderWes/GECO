

#include "PhysicsManager.h"
#include <iostream>
#include <algorithm>

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
	checkCollision();

	solve();

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
			std::shared_ptr<RigidBody> body1 = this->body_list[i];
			std::shared_ptr<RigidBody> body2 = this->body_list[k];
			std::shared_ptr<q3Box> box1 = body1.get()->getBoxCollider();
			std::shared_ptr<q3Box> box2 = body2.get()->getBoxCollider();

			std::shared_ptr<q3Manifold> collision_check_pair = std::make_shared<q3Manifold>();
			q3BoxtoBox(collision_check_pair.get(), box1.get(), box2.get());

			if (collision_check_pair.get()->contactCount > 0)
			{
				CollisionPair collision;
				collision.collision_data = collision_check_pair;
				collision.body1 = body1;
				collision.body2 = body2;

				this->collision_pair_list.push_back(collision);
			}
		}
	}
}

void PhysicsManager::solve()
{
	for (int i = 0; i < collision_pair_list.size(); i++)
	{
		/*  Getting all the required collision data  */
		std::shared_ptr<q3Manifold> collision_pair = collision_pair_list[i].collision_data;
		std::shared_ptr<RigidBody> body_A = collision_pair_list[i].body1;
		std::shared_ptr<RigidBody> body_B = collision_pair_list[i].body2;

		q3Box* box_A = collision_pair.get()->A;
		q3Box* box_B = collision_pair.get()->B;
		
		Point3D contact_position(0);
		float contact_depth = 0;

		for (int i = 0; i < collision_pair.get()->contactCount; i++)
		{
			auto temp_pos = collision_pair.get()->contacts[i].position;
			Point3D contact_(temp_pos[0], temp_pos[1], temp_pos[2]);

			contact_position.value += contact_.value;
			contact_depth = std::max(glm::length(collision_pair.get()->contacts[i].penetration), contact_depth);
		}

		contact_position.value /= collision_pair.get()->contactCount;

		std::cout << "Collision Point: "<< contact_position.value[0] << 
			contact_position.value[1] << contact_position.value[2] << "\n" << std::endl;

		DirectionalVec3 r_A, r_B;
		r_A.value = contact_position.value - body_A.get()->getBodyCentreofMass().value;
		r_B.value = contact_position.value - body_B.get()->getBodyCentreofMass().value;

		auto temp_normal = collision_pair.get()->normal;
		DirectionalVec3 normal(temp_normal[0], temp_normal[1], temp_normal[2]);

		InertiaVector3 inv_J_A, inv_J_B;
		inv_J_A.value = body_A.get()->getInverseInertiaTensor().value;
		inv_J_B.value = body_B.get()->getInverseInertiaTensor().value;

		Mass inv_mass_A, inv_mass_B;
		inv_mass_A.value = 1 / body_A.get()->getMass().value;
		inv_mass_B.value = 1 / body_B.get()->getMass().value;

		VelocityVec3 linear_velocity_A, linear_velocity_B;
		linear_velocity_A.value = body_A.get()->getLinearVelocity().value;
		linear_velocity_B.value = body_B.get()->getLinearVelocity().value;

		AngularVelocityVec3 angular_velocity_A, angular_velocity_B;
		angular_velocity_A.value = body_A.get()->getAngularVelocity().value;
		angular_velocity_B.value = body_B.get()->getAngularVelocity().value;

		float coefficient_of_restitution = std::min(body_A.get()->getRestitution(), body_B.get()->getRestitution());

		/*  Calculating impulse  */
		Impulse impulse;
		impulse.value = calculateCollisionImpulse(inv_J_A, inv_J_B, normal, linear_velocity_A, linear_velocity_B,
			r_A, r_B, inv_mass_A, inv_mass_B, angular_velocity_A, angular_velocity_B, coefficient_of_restitution).value;

	/*  integrating impulse to both bodies  */
		ImpulseVector3 impulse_normal;
		impulse_normal.value = normal.value * impulse.value;

		/*  Linear impulse integration  */
		VelocityVec3 applied_linear_A, applied_linear_B;
		applied_linear_A.value = linear_velocity_A.value + (impulse_normal.value / body_A.get()->getMass().value);
		body_A.get()->setLinearVelocity(applied_linear_A);

		applied_linear_B.value = linear_velocity_B.value - (impulse_normal.value / body_B.get()->getMass().value);
		body_B.get()->setLinearVelocity(applied_linear_B);

		/*  Angular impulse integration  */
		AngularVelocityVec3 applied_angular_A, applied_angular_B;
		applied_angular_A.value = angular_velocity_A.value + impulse.value * inv_J_A.value * glm::cross(r_A.value, normal.value);
		body_A.get()->setAngularVelocity(applied_angular_A);

		applied_angular_B.value = angular_velocity_B.value - impulse.value * inv_J_B.value * glm::cross(r_B.value, normal.value);
		body_B.get()->setAngularVelocity(applied_angular_B);

		/*  depenetrate objects  */
		float halved_contact_depth = contact_depth / 2;

		Point3D push_back_A, push_back_B;
		push_back_A.value = body_A.get()->getBodyCentreofMass().value + (-normal.value * halved_contact_depth);
		body_A.get()->setBodyPosition(push_back_A);

		push_back_B.value = body_B.get()->getBodyCentreofMass().value + (normal.value * halved_contact_depth);
		body_B.get()->setBodyPosition(push_back_B);

		std::cout << "Linear Velocity A: " << applied_linear_A.value[0] <<
			applied_linear_A.value[0] << applied_linear_A.value[0] << std::endl;

		std::cout << "Angular Velocity A: " << applied_angular_A.value[0] <<
			applied_angular_A.value[0] << applied_angular_A.value[0] << std::endl;

		std::cout << "distance A to collision point: " << glm::length(r_A.value) << "\n" << std::endl;

		std::cout << "Linear Velocity B: " << applied_linear_B.value[0] <<
			applied_linear_B.value[0] << applied_linear_B.value[0] << std::endl;

		std::cout << "Angular Velocity B: " << applied_linear_B.value[0] <<
			applied_linear_B.value[0] << applied_linear_B.value[0] << std::endl;

		std::cout << "distance B to collision point: " << glm::length(r_B.value) << "\n\n" << std::endl;

	}
	this->collision_pair_list.clear();
}

PhysicsManager::~PhysicsManager() {

	/*for (auto body : this->body_list)
	{
		delete body;
		body = nullptr;
	}*/
	this->collision_data_list.clear();
	this->collision_pair_list.clear();
	this->body_list.clear();
}

Impulse PhysicsManager::calculateCollisionImpulse(InertiaVector3 inv_J1, InertiaVector3 inv_J2,
	DirectionalVec3 normal, VelocityVec3 V1, VelocityVec3 V2, DirectionalVec3 r1, DirectionalVec3 r2,
	Mass inv_m1, Mass inv_m2, AngularVelocityVec3 w1, AngularVelocityVec3 w2, float Ee) 
{
	/*   Calculating the Numerator   */
	float coefficient = -(1 + Ee);
	float normal_dot_velocities = glm::dot((V1.value - V2.value), normal.value); 
	float angular_dot_distance_normal = glm::dot(w1.value, glm::cross(r1.value, normal.value)) - 
		glm::dot(w2.value, glm::cross(r2.value, normal.value)); 

	float numerator = coefficient * (normal_dot_velocities + angular_dot_distance_normal);

	/*   Calculating the Denominator   */
	float masses = inv_m1.value + inv_m2.value;

	glm::fvec3 normal_r1 = glm::cross(r1.value, normal.value);
	glm::fvec3 J1_mult_rXn = normal_r1 * inv_J1.value;
	float J1_normal_distance = glm::dot(normal_r1, J1_mult_rXn);

	glm::fvec3 normal_r2 = glm::cross(r2.value, normal.value);
	glm::fvec3 J2_mult_rXn = normal_r2 * inv_J2.value;
	float J2_normal_distance = glm::dot(normal_r2, J2_mult_rXn);

	float denominator = masses + (J1_normal_distance + J2_normal_distance);

	/*  Time to put it all together  */
	Impulse impulse;
	impulse.value = numerator / denominator; 

	return impulse;
}