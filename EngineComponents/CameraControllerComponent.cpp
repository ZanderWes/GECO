#include "CameraControllerComponent.h"


CameraControllerComponent::CameraControllerComponent() : CameraComponent()
{
}

CameraControllerComponent::CameraControllerComponent(glm::fvec3 pos, glm::fvec3 forward, 
	glm::fvec3 up, float fov, float aspect, float znear, float zfar) : 
	CameraComponent(pos, forward, up, fov, aspect, znear, zfar)
{
}

void CameraControllerComponent::FreeFloatingCameraTranslate(glm::fvec3 translation)
{
	this->position_ += translation[2] * this->forward_;

	this->position_ += translation[1] * this->up_;

	glm::fvec3 camera_strafe_vector = glm::normalize(glm::cross(this->forward_, this->up_));
	this->position_ += translation[0] * camera_strafe_vector;
}


void CameraControllerComponent::FreeFloatingCameraRotate(glm::fvec3 rotation)
{
	glm::fvec3 temp_forward = glm::normalize(glm::rotate(this->forward_, rotation[0], glm::fvec3(0,1,0)));

	glm::fvec3 camera_up_down_rotation_vector = glm::normalize(glm::cross(this->forward_, glm::fvec3(0, 1, 0)));

	temp_forward += glm::normalize(glm::rotate(this->forward_, rotation[1], camera_up_down_rotation_vector));
	
	glm::fvec3 temp_up = glm::normalize(glm::cross(temp_forward, camera_up_down_rotation_vector));
	temp_up = glm::normalize(glm::rotate(temp_up, rotation[2], temp_forward));
	
	this->forward_ = temp_forward;
	this->up_ = temp_up;
}


void CameraControllerComponent::FPSLookUpDown(float angle)
{

}


void CameraControllerComponent::FPSLookLeftRight(float angle)
{

}

void CameraControllerComponent::FPSRoll(float angle)
{

}

void CameraControllerComponent::FPSMoveForwardBackward(float distance)
{

}

void CameraControllerComponent::FPSMoveLeftRight(float distance)
{

}

void CameraControllerComponent::FPSMoveUpDown(float distance)
{

}


void CameraControllerComponent::GlobalTranslate(glm::fvec3 translate)
{

}


void CameraControllerComponent::GlobalRotate(glm::fvec3 rotate)
{

}