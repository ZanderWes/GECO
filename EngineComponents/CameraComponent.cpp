#include "CameraComponent.h"


CameraComponent::CameraComponent()
{
	position_ = { 0,0,0 };
	forward_ = { 0,0,1 };
	up_ = { 0,1,0 };
	perspective_ = { 90, 600 / 600, 0.01, 10000.0 };
}

CameraComponent::CameraComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec4 perspective)
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

//glm::fmat3 CameraComponent::getCameraViewMatrix()
//{
//	glm::fmat3 temp = {0,0,0 ,0,0,0 ,0,0,0};
//	return temp;
//}
//
//glm::fvec4 CameraComponent::getCameraProjection()
//{
//	return { 0,0,0,0 };
//}
//
//glm::fmat4 CameraComponent::getCameraViewAndProjectionMatrix()
//{
//	glm::fmat4 temp;
//	return temp;
//}