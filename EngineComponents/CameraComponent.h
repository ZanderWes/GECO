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


protected:
	glm::fvec3 position_;
	glm::fvec3 forward_;
	glm::fvec3 up_;
	glm::fvec4 perspective_;

private:


};

