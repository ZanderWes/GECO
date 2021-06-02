#include "Camera.h"

Camera::Camera()
{
	position_ = { 980,300,840 };
	forward_ = { 0,0,1 };
	up_ = {0,1,0};
	perspective_ = {90, 600 / 600, 0.01, 10000.0};
}

Camera::Camera(glm::fvec3 pos, glm::fvec3 forward, glm::fvec4 perspective)
{
	this->position_ = pos;
	this->forward_ = forward; 
	this->up_ = static_up;
	this->perspective_ = perspective;
}

void Camera::rotate(glm::fvec3 rotation)
{
	//glm::fvec3 camera_rotation;
	//apply rotation around up vector first
	//camera_rotation[1] = rotation[1];
	glm::fvec3 tempforward = glm::normalize(glm::rotate(forward_, rotation[0], static_up));
	//this->camera->setForwardVector();

	// calculates the relative up down rotation vector for camera.
	glm::fvec3 camera_up_down_rotation_vector = glm::normalize(glm::cross(this->forward_, this->static_up));

	tempforward += glm::normalize(glm::rotate(forward_, rotation[1], camera_up_down_rotation_vector));

	forward_ = tempforward;
	//up_ = glm::normalize(glm::rotate());

	//camera_rotation[2] = camera_up_down_rotation_vector[0];
	//camera_rotation[2] = camera_up_down_rotation_vector[1];

	
}

void Camera::translate(glm::fvec3 translation)
{
	position_ += translation[2] * forward_;

	glm::fvec3 camera_strafe_vector = glm::normalize(glm::cross(this->forward_, this->static_up));

	position_ += translation[0] * camera_strafe_vector;
}

void Camera::rotateCameraUpDown(float angle)
{

}

void Camera::rotateCameraLeftRight(float angle)
{

}

void Camera::moveCameraLeftRight(float distance)
{

}

void Camera::moveCameraForwardBack(float distance)
{

}

void Camera::setFOVy(float fovY)
{
	this->perspective_[0] = fovY;
}

void Camera::setAspect(float aspect)
{
	this->perspective_[1] = aspect;
}

void Camera::setZNear(float z_near)
{
	this->perspective_[2] = z_near;
}

void Camera::setZFar(float z_far)
{
	this->perspective_[3] = z_far;
}

glm::dmat3 Camera::getCameraView()
{
	return glm::dmat3(position_, forward_ + position_, up_);
}

glm::fvec4 Camera::getCameraPerspective()
{
	return perspective_;
}