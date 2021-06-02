/****************************************************
* @file CameraControllerComponent.h
* @brief header file for the Camera controller component
* 
* @author Zander Wessels
* @date June 2021
* 
****************************************************/

#pragma once

#include "CameraComponent.h"


class CameraControllerComponent : public CameraComponent
{
public:

	CameraControllerComponent();

	CameraControllerComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec4 perspective);

	/**
	 * @brief apply translate to fps style camera 
	 * @param translation
	*/
	void FPSTranslate(glm::fvec3 translation);

	/**
	 * @brief apply rotate to fps style camera
	 * @param rotation 
	*/
	void FPSRotate(glm::fvec3 rotation);

	/**
	 * @brief apply up/down rotation to fps style camera
	 * @param angle 
	*/
	void FPSLookUpDown(float angle);

	/**
	 * @brief apply left/right rotation to fps style camera
	 * @param angle
	*/
	void FPSLookLeftRight(float angle);

	/**
	 * @brief applies translation to camera based of the global world axis.
	 * @param translate 
	*/
	void GlobalTranslate(glm::fvec3 translate);

	/**
	 * @brief applies rotation to camera based of the global world axis.
	 * @param translate
	*/
	void GlobalRotate(glm::fvec3 rotate);

private:
	
	/*glm::fvec3 world_X;
	glm::fvec3 world_Y;
	glm::fvec3 world_Z;*/

};

