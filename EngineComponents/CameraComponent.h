/****************************************************
* @file CameraComponent.h
* @brief header file for the Camera component
*
* @author Zander Wessels
* @date June 2021
*
****************************************************/

#pragma once

#include <glm.hpp>

class CameraComponent
{
public:

	/**
	 * @brief default constructor
	*/
	CameraComponent();

	/**
	 * @brief full constructor
	 * @param pos 
	 * @param forward 
	 * @param perspective 
	*/
	CameraComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec4 perspective);
	
	/**
	 * @brief set the translation of camera
	 * @param position 
	*/
	void setCameraPosition(glm::fvec3 position);

	/**
	 * @brief set the rotation of the camera
	 * @param rotation 
	*/
	void setCameraRotation(glm::fvec3 rotation);

	/**
	 * @brief set the look at point or point of focus of camera
	 * this is also the forward vector of the camera.
	 * @param lookat 
	*/
	void setCameraLookAt(glm::fvec3 lookat);

	glm::fmat3 getCameraViewMatrix();

	glm::fvec4 getCameraProjection();

	glm::fmat4 getCameraViewAndProjectionMatrix();

protected:
	glm::fvec3 position_;
	glm::fvec3 forward_;
	glm::fvec3 up_;
	glm::fvec4 perspective_;

private:


};

