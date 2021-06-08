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

	CameraControllerComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up, //glm::fvec4 perspective);
		float fov, float aspect, float znear, float zfar);

	/**
	 * @brief apply translate to fps style camera 
	 * X axis Translation: translates the camera to its left/right
	 * Y axis Translation: translates the camera to its up
	 * Z Axis Translation: translates the camera in its forward direction
	 * @param translation
	*/
	void FreeFloatingCameraTranslate(glm::fvec3 translation);

	/**
	 * @brief apply rotate to fps style camera
	 * X axis Rotation: local camera lookup/down rotation
	 * Y axis Rotation: local camera left/right rotation
	 * Z Axis Rotation: local camera rolling rotation
	 * @param rotation 
	*/
	void FreeFloatingCameraRotate(glm::fvec3 rotation);

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
	 * @brief rotates camera along its forward vector  
	 * @param angle 
	*/
	void FPSRoll(float angle);

	/**
	 * @brief translates the camera along its relative forward vector
	 * without translating along the up vector
	 * @param distance 
	*/
	void FPSMoveForwardBackward(float distance);

	/**
	 * @brief translates the camera along its relative adjacent vector
	 * without translating along the up vector
	 * @param distance 
	*/
	void FPSMoveLeftRight(float distance);

	/**
	 * @brief translates the camera along its relative up vector
	 * @param distance 
	*/
	void FPSMoveUpDown(float distance);

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

