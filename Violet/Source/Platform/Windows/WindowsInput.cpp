/////////////////
///
/// WindowsInput.cpp
/// Violet McAllister
/// July 11th, 2022
///
/// Windows Implementation of the Input class.
///
/////////////////

#include "vtpch.h"

#include <GLFW/glfw3.h>

#include "Platform/Windows/WindowsInput.h"

#include "Violet/Core/Application.h"

#include "Platform/Windows/WindowsInput.h"

namespace Violet
{
	Input* Input::s_Instance = new WindowsInput();

	/**
	 * @brief Checks if a certain key is pressed.
	 * @param p_KeyCode The key code of the key we're checking.
	 * @returns If a certain key is being pressed.
	 */
	bool WindowsInput::IsKeyPressedImpl(int p_KeyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets the status of a keycode.
		auto state = glfwGetKey(window, p_KeyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	/**
	 * @brief Checks if a mouse button is pressed.
	 * @param p_Button the button code of the button we are checking.
	 * @returns If a certain mouse butotn is being pressed.
	 */
	bool WindowsInput::IsMouseButtonPressedImpl(int p_Button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets the status of a mouse code.
		auto state = glfwGetMouseButton(window, p_Button);
		return state == GLFW_PRESS;
	}

	/**
	 * @brief Gets the mouse position.
	 * @returns The mouse position as a std::pair
	 */
	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		// Gets the cursor position.
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	/**
	 * @brief Gets the mouse X position.
	 * @returns The mouse X position.
	 */
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	/**
	 * @brief Gets the mouse Y position.
	 * @returns The mouse Y position.
	 */
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}