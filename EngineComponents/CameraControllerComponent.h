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


private:
	glm::fvec3 world_up;

};

