/////////////////
///
/// EditorLayer.cpp
/// Violet McAllister
/// July 30th, 2022
///
/// The editor camera is the camera
/// which the Violet Editor uses.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/EditorCamera.h"

#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Violet/Core/Input.h"
#include "Violet/Core/KeyCodes.h"
#include "Violet/Core/MouseCodes.h"

namespace Violet
{
	/**
	 * @brief Constructs an Editor Camera.
	 * @param p_FOV The fielf of view of the camera.
	 * @param p_AspectRatio The aspect ratio of the camera.
	 * @param p_NearClip The near clip of the camera.
	 * @param p_FarClip The far clip of the camera.
	 */
	EditorCamera::EditorCamera(float p_FOV, float p_AspectRatio, float p_NearClip, float p_FarClip)
		: m_FOV(p_FOV), m_AspectRatio(p_AspectRatio), m_NearClip(p_NearClip), m_FarClip(p_FarClip), Camera(glm::perspective(glm::radians(p_FOV), p_AspectRatio, p_NearClip, p_FarClip))
	{
		UpdateView();
	}

	/**
	 * @brief Updates the projection when something has changed. 
	 */
	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	/**
	 * @brief Updates the view matrix when something has changed. 
	 */
	void EditorCamera::UpdateView()
	{
		// m_Yaw = m_Pitch = 0.0f; // Lock the camera's rotation.
		m_Position = CalculatePosition();

		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	/**
	 * @brief Determines what the pan speed of the camera should be.
	 * @returns A set of two values for the x and y pan speeds.
	 */
	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // Max is 2.4u/s.
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // Max is 2.4u/s.
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	/**
	 * @brief Determines what the rotation speed of the camera should be.
	 * @returns The rotation speed.
	 */
	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	/**
	 * @brief Determines the zoom speed of the camera.
	 * @returns The zoom speed.
	 */
	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); // Max Speed is 100u/s.
		return speed;
	}

	/**
	 * @brief Runs when the application is updated and is responsible
	 * for updating the camera position on input.
	 * @param p_Timestep The timestep for the application.
	 */
	void EditorCamera::OnUpdate(Timestep p_Timestep)
	{
		if (Input::IsKeyPressed(Key::LeftAlt))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
			m_InitialMousePosition = mouse;

			// Camera Panning (Alt+Middle Mouse Button)
			if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
				MousePan(delta);
			// Camera Rotation (Alt+Mouse Button Left)
			if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
				MouseRotate(delta);
			// Camera Zooming (Alt+Mouse Button Right)
			if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
				MouseZoom(delta.y);
		}

		UpdateView();
	}

	/**
	 * @brief Runs when an event is called in Violet.
	 * @param p_Event The event information.
	 */
	void EditorCamera::OnEvent(Event& p_Event)
	{
		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<MouseScrolledEvent>(VT_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	/**
	 * @brief Updates the zoom when the mouse is scrolled.
	 * @param p_Event The mouse scrolled event information.
	 * @returns The success of the event.
	 */
	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& p_Event)
	{
		float delta = p_Event.GetYOffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}

	/**
	 * @brief Pans the camera.
	 * @param p_Delta The delta position of the mouse.
	 */
	void EditorCamera::MousePan(const glm::vec2& p_Delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * p_Delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetUpDirection() * p_Delta.y * ySpeed * m_Distance;
	}

	/**
	 * @brief Rotates the camera.
	 * @param p_Delta The delta position of the mouse.
	 */
	void EditorCamera::MouseRotate(const glm::vec2& p_Delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_Yaw += yawSign * p_Delta.x * RotationSpeed();
		m_Pitch += p_Delta.y * RotationSpeed();
	}

	/**
	 * @brief Zoomins in with the camera.
	 * @param p_Delta of the y position of the mouse.
	 */
	void EditorCamera::MouseZoom(float p_Delta)
	{
		m_Distance -= p_Delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	/**
	 * @brief Determines what the angle would be for the camera to turn up.
	 * @returns The direction as a vector.
	 */
	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	/**
	 * @brief Determines what the angle would be for the camera to turn right.
	 * @returns The direction as a vector.
	 */
	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	/**
	 * @brief Determines what the angle would be for the camera to turn forward.
	 * @returns The direction as a vector.
	 */
	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	/**
	 * @brief Calculates the position of the camera.
	 * @returns The position of the camera.
	 */
	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	/**
	 * @brief Determines the orientation of the camera.
	 * @returns The orientation of the camera as a quaternion.
	 */
	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
}
