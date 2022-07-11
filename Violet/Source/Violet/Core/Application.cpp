/////////////////
///
/// Application.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 1st, 2022
///
/// Contains class implementations for the Application
/// object.
///
/////////////////

#include "vtpch.h"

#include <GLFW/glfw3.h>

#include "Violet/Core/Application.h"
#include "Violet/Core/Log.h"
#include "Violet/Events/ApplicationEvent.h"

namespace Violet
{
	/**
	 * @brief Constructs an Application object.
	 */
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	/**
	 * @brief Destructs an Application object.
	 */
	Application::~Application()
	{

	}

	/**
	 * @brief Contains the main run loop and handles updating the application.
	 */
	void Application::Run()
	{
		while (m_Running)
		{
			// Sets what the window should clear to.
			glClearColor(1, 0, 1, 1);
			// Clears the screen of pixels.
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}