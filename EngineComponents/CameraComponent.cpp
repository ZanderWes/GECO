#include "CameraComponent.h"


CameraComponent::CameraComponent() 
{
	position_ = { 0,0,0 };
	forward_ = { 0,0,1 };
	up_ = { 0,1,0 };
	//perspective_ = { 90, 600 / 600, 0.01, 10000.0 };
	FOV_ = 60.0f;
	aspect_ = 1.0f;
	z_near_ = 0.01f;
	z_far_ = 10000.0f;
}

CameraComponent::CameraComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up, //glm::fvec4 perspective);
	float fov, float aspect, float znear, float zfar) : position_(pos), forward_(forward),
	up_(up), FOV_(fov), aspect_(aspect), z_near_(znear), z_far_(zfar)
{
}

void CameraComponent::setCameraPosition(glm::fvec3 position)
{

}

void CameraComponent::setCameraRotation(glm::fvec3 rotation)
{

}

void CameraComponent::setCameraLookAt(glm::fvec3 lookat)
{

}

glm::fmat3 CameraComponent::getCameraViewMatrix()
{
	return glm::fmat3( this->position_, this->forward_, this->up_ );
}

glm::fvec4 CameraComponent::getCameraPerspective()
{
	return glm::fvec4(FOV_, aspect_, z_near_, z_far_);
}

glm::fmat4 CameraComponent::getCameraViewAndPerspectiveMatrix()
{
	glm::fmat4 temp = {position_[0], position_[1], position_[2], 0, 
		forward_[0], forward_[1], forward_[2], 0, up_[0], up_[1], up_[2],0, 
		FOV_, aspect_, z_near_, z_far_ };
	return temp;
}