/////////////////
///
/// SceneCamera.h
/// Violet McAllister
/// July 23rd, 2022
///
/// A camera used by the scene as a way to
/// navigate scenes.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_CAMERA_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_CAMERA_H_INCLUDED__

#include "Violet/Renderer/Camera.h"

namespace Violet
{
	/**
	 * @brief Scene specific camera for Violet Engine.
	 */
	class SceneCamera : public Camera
	{
	public: // Constructors & Deconstructors
		SceneCamera();
		virtual ~SceneCamera() = default;
	public: // Getters & Setters
		void SetOrthographic(float p_Size, float p_NearClip, float p_FarClip);
		void SetViewportSize(uint32_t p_Width, uint32_t p_Height);

		/**
		 * @brief Gets the orthographic size.
		 * @returns The orthographic size.
		 */
		float GetOrthographicSize() const { return m_OrthographicSize; }

		/**
		 * @brief Sets the orthographic size.
		 * @param p_Size The orthographic size.
		 */
		void SetOrthographicSize(float p_Size) { m_OrthographicSize = p_Size; RecalculateProjection(); }
	private: // Helpers
		void RecalculateProjection();
	private: // Private Member Variables
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
		float m_AspectRatio = 0.0f;
	};
}

#endif // __VIOLET_ENGINE_SCENE_CAMERA_H_INCLUDED__