/////////////////
///
/// Math.cpp
/// Violet McAllister
/// July 30th, 2022
///
/// Defines mathematics functions to use
/// in Violet.
///
/////////////////

#include "vtpch.h"

#include "Violet/Math/Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Violet
{
	namespace Math
	{
		/**
		 * @brief Takes a transform and breaks it down into its
		 * translation, rotation, and scale.
		 * @param p_Transform The transform to decompose.
		 * @param p_OutTranslation The translation.
		 * @param p_OutRotation The rotation.
		 * @param p_OutScale The scale.
		 * @returns The success of the decomposition.
		 */
		bool DecomposeTransform(const glm::mat4& p_Transform, glm::vec3& p_OutTranslation, glm::vec3& p_OutRotation, glm::vec3& p_OutScale)
		{
			glm::mat4 localMatrix(p_Transform);

			// Normalize Matrix
			if (glm::epsilonEqual(localMatrix[3][3], static_cast<float>(0), glm::epsilon<float>()))
				return false;

			// Isolate Perspective
			if (
				glm::epsilonNotEqual(localMatrix[0][3], static_cast<float>(0), glm::epsilon<float>()) ||
				glm::epsilonNotEqual(localMatrix[1][3], static_cast<float>(0), glm::epsilon<float>()) ||
				glm::epsilonNotEqual(localMatrix[2][3], static_cast<float>(0), glm::epsilon<float>()))
			{
				// Clear Perspective
				localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = static_cast<float>(0);
				localMatrix[3][3] = static_cast<float>(1);
			}

			// Translation
			p_OutTranslation = glm::vec3(localMatrix[3]);
			localMatrix[3] = glm::vec4(0, 0, 0, localMatrix[3].w);

			glm::vec3 row[3], pdum3;

			// Scale & Shear
			for (glm::length_t i = 0; i < 3; ++i)
				for (glm::length_t j = 0; j < 3; ++j)
					row[i][j] = localMatrix[i][j];

			// Compute X scale factor and normalize first row.
			p_OutScale.x = glm::length(row[0]);
			row[0] = glm::detail::scale(row[0], static_cast<float>(1));
			p_OutScale.y = glm::length(row[1]);
			row[1] = glm::detail::scale(row[1], static_cast<float>(1));
			p_OutScale.z = glm::length(row[2]);
			row[2] = glm::detail::scale(row[2], static_cast<float>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
#if 0
			pdum3 = glm::cross(row[1], row[2]);
			if (glm::dot(row[0], pdum3) < 0)
			{
				for (glm::length_t i = 0; i < 3; i++)
				{
					p_OutScale[i] *= static_cast<float>(-1);
					row[i] *= static_cast<float>(-1);
				}
			}
#endif

			// Rotation
			p_OutRotation.y = asin(-row[0][2]);
			if (cos(p_OutRotation.y) != 0)
			{
				p_OutRotation.x = atan2(row[1][2], row[2][2]);
				p_OutRotation.z = atan2(row[0][1], row[0][0]);
			}
			else
			{
				p_OutRotation.x = atan2(-row[2][0], row[1][1]);
				p_OutRotation.z = 0;
			}

			return true;
		}
	}
}
