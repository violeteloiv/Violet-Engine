/////////////////
///
/// OrthographicCamera.h
/// Violet McAllister
/// July 12th, 2022
/// Updated July 13th, 2022
///
/// An Orthographic Camera is a camera which
/// shoots parallel rays from a camera. All
/// objects appear the same in size despite their
/// distance from the lens.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_H_INCLUDED__

#include <glm/glm.hpp>

namespace Violet
{
	class OrthographicCamera
	{
	public: // Constructors
		OrthographicCamera(float p_Left, float p_Right, float p_Bottom, float p_Top);
	public: // Getters & Setters
		void SetProjection(float p_Left, float p_Right, float p_Bottom, float p_Top);
	public: // Getters & Setters
		/**
		 * @brief Gets the camera position.
		 * @returns The camera position.
		 */
		const glm::vec3& GetPosition() const { return m_Position; }

		/**
		 * @brief Sets the camera position.
		 * @param p_Position The camera position.
		 */
		void SetPosition(const glm::vec3& p_Position) { m_Position = p_Position; RecalculateViewMatrix(); }

		/**
		 * @brief Gets the camera rotation.
		 * @returns The camera position.
		 */
		float GetRotation() const { return m_Rotation; }

		/**
		 * @brief Sets the camera rotation.
		 * @param p_Rotation The camera rotation.
	     */
		void SetRotation(float p_Rotation) { m_Rotation = p_Rotation; RecalculateViewMatrix(); }

		/**
		 * @brief Gets the projection matrix.
		 * @returns The projection matrix.
		 */
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

		/**
		 * @brief Gets the view matrix.
		 * @returns The view matrix.
		 */
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		/**
		 * @brief Gets the view projection matrix.
		 * @returns The view projection matrix.
		 */
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private: // Helpers
		void RecalculateViewMatrix();
	private: // Matrix Info
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	private: // Camera Info
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_H_INCLUDED__