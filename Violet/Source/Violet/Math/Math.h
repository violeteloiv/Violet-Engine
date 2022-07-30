/////////////////
///
/// Math.h
/// Violet McAllister
/// July 30th, 2022
///
/// Defines mathematics functions to use
/// in Violet.
///
/////////////////

#ifndef __VIOLET_ENGINE_MATH_H_INCLUDED__
#define __VIOLET_ENGINE_MATH_H_INCLUDED__

#include <glm/glm.hpp>

namespace Violet
{
	namespace Math
	{
		bool DecomposeTransform(const glm::mat4& p_Transform, glm::vec3& p_OutTransform, glm::vec3& p_OutRotation, glm::vec3& p_OutScale);
	}
}

#endif // __VIOLET_ENGINE_MATH_H_INCLUDED__
