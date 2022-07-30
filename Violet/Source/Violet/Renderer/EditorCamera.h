/////////////////
///
/// EditorLayer.h
/// Violet McAllister
/// July 30th, 2022
///
/// The editor camera is the camera
/// which the Violet Editor uses.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_EDITOR_CAMERA_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_EDITOR_CAMERA_H_INCLUDED__

#include <glm/glm.hpp>

#include "Violet/Core/Timestep.h"
#include "Violet/Events/Event.h"
#include "Violet/Events/MouseEvent.h"
#include "Violet/Renderer/Camera.h"

namespace Violet
{
	/**
	 * @brief The editor camera for violet editor. 
	 */
	class EditorCamera : public Camera
	{
	public: // Constructors
		EditorCamera() = default;
		EditorCamera(float p_FOV, float p_AspectRatio, float p_NearClip, float p_FarClip);
	public: // Violet Internals
		void OnUpdate(Timestep p_Timestep);
		void OnEvent(Event& p_Event);
	public: // Getters & Setters
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		glm::quat GetOrientation() const;

		/**
		 * @brief Gets the distance for the camera.
		 * @returns The distance for the camera.
		 */
		inline float GetDistance() const { return m_Distance; }

		/**
		 * @brief Sets the distance for the camera.
		 * @param p_Distance The new distance for the camera.
		 */
		inline void SetDistance(float p_Distance) { m_Distance = p_Distance; }

		/**
		 * @brief Sets the viewport size for the camera.
		 * @param p_Width The width of the new viewport.
		 * @param p_Height The height of the new viewport.
		 */
		inline void SetViewportSize(float p_Width, float p_Height) { m_ViewportWidth = p_Width; m_ViewportHeight = p_Height; UpdateProjection(); }

		/**
		 * @brief Gets the view matrix for the camera.
		 * @returns The view matrix for the camera.
		 */
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		/**
		 * @brief Gets the view projection of the camera.
		 * @returns The view projection of the camera.
		 */
		glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

		/**
		 * @brief Gets the position of the camera.
		 * @returns The position of the camera.
		 */
		const glm::vec3& GetPosition() const { return m_Position; }

		/**
		 * @brief Gets the pitch of the camera.
		 * @returns The pitch of the camera.
		 */
		float GetPitch() const { return m_Pitch; }

		/**
		 * @brief Gets the yaw of the camera.
		 * @returns The yaw of the camera.
		 */
		float GetYaw() const { return m_Yaw; }
	private: // Helpers
		void UpdateProjection();
		void UpdateView();
		glm::vec3 CalculatePosition() const;
	private: // Event
		bool OnMouseScroll(MouseScrolledEvent& p_Event);
	private: // Functionality
		void MousePan(const glm::vec2& p_Delta);
		void MouseRotate(const glm::vec2& p_Delta);
		void MouseZoom(float p_Delta);
		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private: // Private Member Variables
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_EDITOR_CAMERA_H_INCLUDED__
