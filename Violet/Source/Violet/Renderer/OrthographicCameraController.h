/////////////////
///
/// OrthographicCameraController.h
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 14th, 2022
///
/// Controller for an Orthographic Controller.
/// 
/// WASD to move the camera.
/// QE to rotate the camera.
/// Zoom by scrolling.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_INCLUDED__

#include "Violet/Core/Timestep.h"
#include "Violet/Events/ApplicationEvent.h"
#include "Violet/Events/MouseEvent.h"
#include "Violet/Renderer/OrthographicCamera.h"

namespace Violet
{
	/**
	 * @brief Controller for an Orthographic Camera. 
	 */
	class OrthographicCameraController
	{
	public: // Constructor
		OrthographicCameraController(float p_AspectRatio, bool p_Rotation = false);
	public: // Main Functionality
		void OnUpdate(Timestep p_Timestep);
		void OnEvent(Event& p_Event);
	public: // Getters
		/**
		 * @brief Gets the camera.
		 * @returns The camera.
		 */
		OrthographicCamera& GetCamera() { return m_Camera; }

		/**
		 * @brief Gets the const camera.
		 * @returns The const camera.
		 */
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		/**
		 * @brief Gets the zoom level.
		 * @returns The zoom level.
		 */
		float GetZoomLevel() const { return m_ZoomLevel; }

		/**
		 * @brief Sets the zoom level.
		 * @param p_ZoomLevel The zoom level being set.
		 */
		void SetZoomLevel(float p_ZoomLevel) { m_ZoomLevel = p_ZoomLevel; }
	private: // Events
		bool OnMouseScrolled(MouseScrolledEvent& p_Event);
		bool OnWindowResized(WindowResizeEvent& p_Event);
	private: // Camera Settings
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;
	private: // Camera Transform
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_ORTHOGRAPHIC_CAMERA_CONTROLLER_H_INCLUDED__