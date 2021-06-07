#include "CameraComponent.h"


CameraComponent::CameraComponent()
{
	position_ = { 0,0,0 };
	forward_ = { 0,0,1 };
	up_ = { 0,1,0 };
	perspective_ = { 90, 600 / 600, 0.01, 10000.0 };
}

CameraComponent::CameraComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up, glm::fvec4 perspective)
{
	position_ = pos;
	forward_ = forward;
	up_ = up;
	perspective_ = perspective;
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

glm::fvec4 CameraComponent::getCameraProjection()
{
	return this->perspective_;
}

glm::fmat4 CameraComponent::getCameraViewAndProjectionMatrix()
{
	glm::fmat4 temp = {position_[0], position_[1], position_[2], 0, 
		forward_[0], forward_[1], forward_[2], 0, up_[0], up_[1], up_[2],0, 
		perspective_[0], perspective_[1], perspective_[2], perspective_[3] };
	return temp;
}