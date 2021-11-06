#pragma once

#include "PhysicsManager.h"

static class TestClass 
{
public:

	static inline void TestImpulseEquation() 
	{
		std::cout << "UNIT TEST LAMBDA!!!" << "\n" << std::endl;

		VelocityVec3 V1, V2;
		AngularVelocityVec3 W1, W2;
		Mass inv_m1, inv_m2;
		InertiaVector3 inv_J1, inv_J2;
		DirectionalVec3 R1, R2, normal;
		float corelation_of_restitution = 0.6;

		V1.value = glm::fvec3(0, -10, 0);
		W1.value = glm::fvec3(0, 0, 0);
		inv_m1.value = 1;
		inv_J1.value = glm::fvec3(9.6, 24.0, 9.6);
		R1.value = glm::fvec3(2, 2, 2.5) - glm::fvec3(2, 2, 3);

		V2.value = glm::fvec3(0, 0, 0);
		W2.value = glm::fvec3(0, 0, 0);
		inv_m2.value = 1 / 3.0f;
		inv_J2.value = glm::fvec3(0.2222, 0.4, 0.4);
		R2.value = glm::fvec3(2, 2, 2.5) - glm::fvec3(2, 2, 2);

		normal.value = glm::fvec3(0, 1, 0);

		double lambda = PhysicsManager::calculateCollisionImpulse(inv_J1, inv_J2, normal,
			V1, V2, R1, R2, inv_m1, inv_m2, W1, W2, corelation_of_restitution).value;

		std::cout << "body 1 mass: " << 1 / inv_m1.value << "\nbody 2 mass: " << 1 / inv_m2.value << std::endl;

		std::cout << "body 1 Inertia Tensor: " << 1 / inv_m1.value << "\nbody 2 Inertia Tensor: " << 1 / inv_m2.value << std::endl;

		std::cout << "body 1 Linear Velocity: " << V1.value[0] << ", " << V1.value[1] << ", " << V1.value[2] <<
			"\nbody 2 Linear Velocity: " << V2.value[0] << ", " << V2.value[1] << ", " << V2.value[2] << std::endl;

		

		std::cout << "body 1 Angular Velocity: " << W1.value[0] << ", " << W1.value[1] << ", " << W1.value[2] <<
			"\nbody 2 Angular Velocity: " << W2.value[0] << ", " << W2.value[1] << ", " << W2.value[2] << std::endl;

		std::cout << "body 1 mass: " << 1 / inv_m1.value << "\nbody 2 mass: " << 1 / inv_m2.value << std::endl;
		std::cout << "\ncalculated lambda: " << lambda << "\n True lambda: " << 4.2227 << "\n\n" << std::endl;
	}


};