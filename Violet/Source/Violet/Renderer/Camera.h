/////////////////
///
/// Camera.h
/// Violet McAllister
/// July 22nd, 2022
/// Updted: July 23rd, 2022
///
/// A camera object that is agnostic to the type
/// of camera used.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_CAMERA_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_CAMERA_H_INCLUDED__

#include <glm/glm.hpp>

namespace Violet
{
	/**
	 * @brief A camera object for use in the
	 * entity component system.
	 */
	class Camera
	{
	public: // Constructor
		Camera() = default;
		virtual ~Camera() = default;

		/**
		 * @brief Constructs a camera object.
		 * @param p_Projection The camera projection.
		 */
		Camera(const glm::mat4& p_Projection)
			: m_Projection(p_Projection) {}
	public: // Getter
		/**
		 * @brief Gets the projection of the camera.
		 * @returns The projection of the camera.
		 */
		const glm::mat4& GetProjection() const { return m_Projection; }
	protected: // Protected Member Variables
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_CAMERA_H_INCLUDED__