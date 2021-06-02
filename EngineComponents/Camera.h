#pragma once
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

class Camera
{
public:
	Camera();

	Camera(glm::fvec3 pos, glm::fvec3 forward, glm::fvec4 perspective);

	/**
	 * @brief rotates camera on its relative X and Y axis
	 * NOTE z axis rotation is disabled for camera.
	 * @param rotationVec Maths::Fvec3
	*/
	void rotate(glm::fvec3 rotationVec);

	/**
	 * @brief translates the camera on its relative XYZ axis
	 * NOTE: if translation is for player, physics translations,
	 * displacements and impulses should be already done this is
	 * the final aplication of translations on update.
	 * @param translation
	*/
	void translate(glm::fvec3 translation);

	/**
	 * @brief rotates the camera up and down based on the angle
	 * @param angle
	*/
	void rotateCameraUpDown(float angle);

	/**
	 * @brief rotates the camera left and right based on the angle
	 * @param angle
	*/
	void rotateCameraLeftRight(float angle);

	/**
	 * @brief translates the camera left and right relative to the
	 * forward viewing vector
	 * NOTE if translation is for player, physics translations,
	 * displacements and impulses should be already done this is
	 * the final aplication of translations on update.
	 * @param distance
	*/
	void moveCameraLeftRight(float distance);

	/**
	 * @brief translates the camera forward and backward relative to
	 * the forward viewing vector
	 * NOTE if translation is for player, physics translations,
	 * displacements and impulses should be already done this is
	 * the final aplication of translations on update.
	 * @param distance
	*/
	void moveCameraForwardBack(float distance);

	/**
	 * @brief setter for camera FOV on y axis
	 * @param fovY
	*/
	void setFOVy(float fovY);

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

	glm::dmat3 getCameraView();

	glm::fvec4 getCameraPerspective();

	/**
	 * @brief returns the float* reference of camera viewing matrix
	 * @return
	*/
	float* getCameraData();
protected:

private:
    glm::fvec3 position_;
    glm::fvec3 forward_;
    glm::fvec3 up_;
	glm::fvec4 perspective_;
	const glm::fvec3 static_up = { 0,1,0 };
};

