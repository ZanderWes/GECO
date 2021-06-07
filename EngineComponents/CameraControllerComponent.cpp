#include "CameraControllerComponent.h"


CameraControllerComponent::CameraControllerComponent() : CameraComponent()
{
}

CameraControllerComponent::CameraControllerComponent(glm::fvec3 pos, glm::fvec3 forward, glm::fvec3 up, glm::fvec4 perspective) :
	CameraComponent(pos, forward, up, perspective)
{
}

void CameraControllerComponent::FPSTranslate(glm::fvec3 translation)
{

}


void CameraControllerComponent::FPSRotate(glm::fvec3 rotation)
{

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