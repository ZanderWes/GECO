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
#include <gtx/rotate_vector.hpp>

class CameraComponent
{
public:

	/**
	 * @brief default constructor
	*/
	CameraComponent();

	/**
	 * @brief full constructor
	 * @param pos position vector
	 * @param forward vector
	 * @param up vector
	 * @param fov 
	 * @param aspect 
	 * @param znear 
	 * @param zfar 
	*/
	CameraComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up, //glm::fvec4 perspective);
		float fov, float aspect, float znear, float zfar);
	
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

	/**
	 * @brief set the forward vector of the cmera view direction
	 * @param forward 
	*/
	void setCameraForward(glm::fvec3 forward);

	/**
	 * @brief setter for camera FOV on y axis
	 * @param fovY
	*/
	void setFieldOfView(float fov);

	/**
	 * @brief setter for camera aspect
	 * @param aspect
	*/
	void setAspect(float aspect);

	/**
	 * @brief setter for the camera near view lens
	 * @param z_near
	*/
	void setZNear(float z_near);

	/**
	 * @brief setter for the camera far view lens
	 * @param z_far
	*/
	void setZFar(float z_far);

	/**
	 * @brief returns the camera view matrix
	 * [position vector]
	 * [forward vector]
	 * [up vector]
	 * @return 
	*/
	glm::dmat3 getCameraViewMatrix();

	/**
	 * @brief returns the camera projection matrix
	 * [
	 * @return projection as float vector 4
	*/
	glm::fvec4 getCameraPerspective();

	/**
	 * @brief 
	 * @return 
	*/
	glm::fmat4 getCameraViewAndPerspectiveMatrix();

	glm::fvec3 getCameraPosition();

protected:
	glm::fvec3 position_;
	glm::fvec3 forward_;
	glm::fvec3 up_;
	glm::fvec3 look_at_;
	//glm::fvec4 perspective_;

	float FOV_;
	float aspect_;
	float z_near_;
	float z_far_;

private:


};

