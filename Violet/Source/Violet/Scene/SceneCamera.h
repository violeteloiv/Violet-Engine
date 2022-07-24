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
	public: // Perspective Type
		/**
		 * @brief Allows the user to determine the current
		 * projection type.
		 */
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public: // Constructors & Deconstructors
		SceneCamera();
		virtual ~SceneCamera() = default;
	public: // Getters & Setters
		void SetOrthographic(float p_Size, float p_NearClip, float p_FarClip);
		void SetPerspective(float p_VerticalFOV, float p_NearClip, float p_FarClip);
		void SetViewportSize(uint32_t p_Width, uint32_t p_Height);

		/**
		 * @brief Gets the perspective vertical field of view.
		 * @returns The perspective vertical field of view.
		 */
		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }

		/**
		 * @brief Sets the perspective vertical field of view.
		 * @param p_VerticalFOV The perspective vertical field of view.
		 */
		void SetPerspectiveVerticalFOV(float p_VerticalFOV) { m_PerspectiveFOV = p_VerticalFOV; RecalculateProjection(); }

		/**
		 * @brief Gets the perspective near clip.
		 * @returns The perspective near clip.
		 */
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }

		/**
		 * @brief Sets the perspective near clip.
		 * @param p_NearClip The perspective near clip.
		 */
		void SetPerspectiveNearClip(float p_NearClip) { m_PerspectiveNear = p_NearClip; RecalculateProjection(); }
		
		/**
		 * @brief Gets the perspective far clip.
		 * @returns The perspective far clip.
		 */
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }

		/**
		 * @brief Sets the perspective far clip.
		 * @param p_FarClip The perspective far clip.
		 */
		void SetPerspectiveFarClip(float p_FarClip) { m_PerspectiveFar = p_FarClip; RecalculateProjection(); }

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

		/**
		 * @brief Gets the orthographic near clip.
		 * @returns The orthographic near clip.
		 */
		float GetOrthographicNearClip() const { return m_OrthographicNear; }

		/**
		 * @brief Sets the orthographic near clip.
		 * @param p_NearClip The orthographic near clip.
		 */
		void SetOrthographicNearClip(float p_NearClip) { m_OrthographicNear = p_NearClip; RecalculateProjection(); }

		/**
		 * @brief Gets the orthographic far clip.
		 * @returns The orthographic far clip.
		 */
		float GetOrthographicFarClip() const { return m_OrthographicFar; }

		/**
		 * @brief Sets the orthographic far clip.
		 * @param p_FarClip The orthographic far clip.
		 */
		void SetOrthographicFarClip(float p_FarClip) { m_OrthographicFar = p_FarClip; RecalculateProjection(); }

		/**
		 * @brief Gets the current projection type.
		 * @returns The current projection type.
		 */
		ProjectionType GetProjectionType() const { return m_ProjectionType; }

		/**
		 * @brief Sets the current projection type.
		 * @param p_Type The new projection type.
		 */
		void SetProjectionType(ProjectionType p_Type) { m_ProjectionType = p_Type; RecalculateProjection(); }
	private: // Helpers
		void RecalculateProjection();
	private: // Private Member Variables
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
		float m_AspectRatio = 0.0f;
	};
}

#endif // __VIOLET_ENGINE_SCENE_CAMERA_H_INCLUDED__
