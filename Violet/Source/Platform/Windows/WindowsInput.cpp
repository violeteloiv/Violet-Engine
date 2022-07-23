/////////////////
///
/// WindowsInput.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 23rd, 2022
///
/// Windows Implementation of the Input class.
///
/////////////////

#include "vtpch.h"

#include <GLFW/glfw3.h>

#include "Violet/Core/Application.h"
#include "Violet/Core/Input.h"

namespace Violet
{
	/**
	 * @brief Checks if a certain key is pressed.
	 * @param p_KeyCode The key code of the key we're checking.
	 * @returns If a certain key is being pressed.
	 */
	bool Input::IsKeyPressed(const KeyCode p_KeyCode)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets the status of a keycode.
		auto state = glfwGetKey(window, static_cast<int32_t>(p_KeyCode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	/**
	 * @brief Checks if a mouse button is pressed.
	 * @param p_Button the button code of the button we are checking.
	 * @returns If a certain mouse butotn is being pressed.
	 */
	bool Input::IsMouseButtonPressed(const MouseCode p_Button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets the status of a mouse code.
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(p_Button));
		return state == GLFW_PRESS;
	}

	/**
	 * @brief Gets the mouse position.
	 * @returns The mouse position as a glm::vec2
	 */
	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		// Gets the cursor position.
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	/**
	 * @brief Gets the mouse X position.
	 * @returns The mouse X position.
	 */
	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	/**
	 * @brief Gets the mouse Y position.
	 * @returns The mouse Y position.
	 */
	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}
