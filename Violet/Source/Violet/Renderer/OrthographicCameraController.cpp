/////////////////
///
/// OrthographicCameraController.cpp
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 15th, 2022
///
/// Controller for an Orthographic Controller.
/// 
/// WASD to move the camera.
/// QE to rotate the camera.
/// Zoom by scrolling.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/OrthographicCameraController.h"

#include "Violet/Core/Input.h"
#include "Violet/Core/KeyCodes.h"

namespace Violet
{
	/**
	 * @brief Constructs an OrthographicCamera Controller.
	 * @param p_AspectRatio The aspect ratio of the screen.
	 * @param p_Rotation Whether rotation is allowed or not.
	 */
	OrthographicCameraController::OrthographicCameraController(float p_AspectRatio, bool p_Rotation)
		: m_AspectRatio(p_AspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(p_Rotation)
	{

	}

	/**
	 * @brief Updates the orthographic camera when the application updates.
	 * @param p_Timestep The delta time of the application.
	 */
	void OrthographicCameraController::OnUpdate(Timestep p_Timestep)
	{
		VT_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(VT_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
		}
		else if (Input::IsKeyPressed(VT_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
		}

		if (Input::IsKeyPressed(VT_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
			m_CameraPosition.y +=  cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
		}
		else if (Input::IsKeyPressed(VT_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
			m_CameraPosition.y -=  cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * p_Timestep;
		}

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(VT_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * p_Timestep;
			if (Input::IsKeyPressed(VT_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * p_Timestep;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	/**
	 * @brief Connects the camera controller with on event.
	 * @param p_Event The event being checked.
	 */
	void OrthographicCameraController::OnEvent(Event& p_Event)
	{
		VT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<MouseScrolledEvent>(VT_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(VT_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	/**
	 * @brief Runs when the mousewheel is scrolled.
	 * @param p_Event Contains mouse event info.
	 * @returns The success of the event.
	 */
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& p_Event)
	{
		VT_PROFILE_FUNCTION();

		m_ZoomLevel -= p_Event.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	/**
	 * @brief Runs when the window is resized.
	 * @param p_Event Contains window info.
	 * @returns The success of the event.
	 */
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& p_Event)
	{
		VT_PROFILE_FUNCTION();

		m_AspectRatio = (float)p_Event.GetWidth() / (float)p_Event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}