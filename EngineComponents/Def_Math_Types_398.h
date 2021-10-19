/**
 * @file Def_Math_Types_398.h
 * @author Zander Wessels
 * @brief Re-declaring math types to ensure type  
 * consistency during physics calculations. 
 * @version 0.1
 * @date 2021-09-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <glm.hpp>

/**
 * @brief single float velocity type 
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Velocity
{
    float value;
    inline Velocity(){}
    inline Velocity(float velocity){value = velocity;}
};

/**
 * @brief single float acelleration type 
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Acceleration
{
    float value;
    inline Acceleration(){}
    inline Acceleration(float accel){value = accel;}
};

/**
 * @brief single float inertia type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Inertia
{
    float  value;
    inline Inertia(){}
    inline Inertia(float inertia){value = inertia;}
};


/**
 * @brief single float force type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Force
{
    float value;
    inline Force(){}
    inline Force(float force){value = force;}
};

/**
 * @brief single float torque type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Torque
{
    float value;
    inline Torque(){}
    inline Torque(float torque){value = torque;}
};

/**
 * @brief single float mass type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Mass
{
    float value;
    inline Mass(){}
    inline Mass(float mass){value = mass;}
};

/**
 * @brief single float length type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Length
{
    float value;
    inline Length(){}
    inline Length(float len){value = len;}
};

/**
 * @brief Vector3 point in 3D world
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct Point3D
{
    glm::fvec3 value;
    inline Point3D(){}
    inline Point3D(float num){value = glm::fvec3(num,num,num);}
    inline Point3D(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief Vector3 velocity type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct VelocityVec3
{
    glm::fvec3 value;
    inline VelocityVec3(){}
    inline VelocityVec3(float num){value = glm::fvec3(num,num,num);}
    inline VelocityVec3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief Vector3 angular velocity type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct AngularVelocityVec3
{
    glm::fvec3 value;
    inline AngularVelocityVec3(){}
    inline AngularVelocityVec3(float num){value = Vector3(num,num,num);}
    inline AngularVelocityVec3(float x,float y,float z){value = Vector3(x,y,z);}
};

/**
 * @brief Vector3 acceleration type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct AccelerationVec3
{
    glm::fvec3 value;
    inline AccelerationVec3(){}
    inline AccelerationVec3(float num){value = glm::fvec3(num,num,num);}
    inline AccelerationVec3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief Vector3 directional force type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct DirectionalForce
{
    glm::fvec3 value;
    inline DirectionalForce(){}
    inline DirectionalForce(float num){value = glm::fvec3(num,num,num);}
    inline DirectionalForce(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief Vector3 vector torque type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct TorqueVector3
{
    glm::fvec3 value;
    inline TorqueVector3(){}
    inline TorqueVector3(float num){value = glm::fvec3(num,num,num);}
    inline TorqueVector3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};


/**
 * @brief Vector3 directional vector type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct DirectionalVec3
{
    glm::fvec3 value;
    inline DirectionalVec3(){}
    inline DirectionalVec3(float num){value = glm::fvec3(num,num,num);}
    inline DirectionalVec3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief Vector3 inertia vector type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct InertiaVector3
{
    glm::fvec3 value;
    inline InertiaVector3(){}
    inline InertiaVector3(float num){value = glm::fvec3(num,num,num);}
    inline InertiaVector3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};

/**
 * @brief inertia Matrix 3x3 type: glm::fmat3
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct InertiaMatrix3
{
	glm::fmat3 value;
	inline InertiaMatrix3(){}
	inline InertiaMatrix3(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz){ value = glm::fmat3(xx, xy, xz, yx, yy, yz, zx, zy, zz); }
	inline InertiaMatrix3(const glm::fvec3 &row0, const glm::fvec3 &row1, const glm::fvec3 &row2) { value = glm::fmat3(row0, row1, row2); }
	//inline InertiaMatrix3(const Vector3 &p_euler) {value = Basis(p_euler);}
	//inline InertiaMatrix3(const Vector3 &p_euler, const Vector3 &p_scale) {value = glm::fmat3(p_euler, p_scale);}
    //inline InertiaMatrix3(const Vector3 &p_axis, real_t p_phi) {value = Basis(p_axis, p_phi);}
	//inline InertiaMatrix3(const Vector3 &p_axis, real_t p_phi, const Vector3 &p_scale) {value = Basis(p_axis, p_phi, p_scale);}
};

/**
 * @brief Vector3 impulse vector type
 * Global accesor name is 'value'
 * e.g. variable_name.value
 */
struct ImpulseVector3
{
    glm::fvec3 value;
    inline ImpulseVector3(){}
    inline ImpulseVector3(float num){value = glm::fvec3(num,num,num);}
    inline ImpulseVector3(float x,float y,float z){value = glm::fvec3(x,y,z);}
};