/////////////////
///
/// Application.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 11th, 2022
///
/// Contains class implementations for the Application
/// object.
///
/////////////////

#include "vtpch.h"

#include <GLFW/glfw3.h>

#include "Violet/Core/Application.h"
#include "Violet/Core/Log.h"

namespace Violet
{
	// Bind Event Function Macro
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	/**
	 * @brief Constructs an Application object.
	 */
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	/**
	 * @brief Destructs an Application object.
	 */
	Application::~Application()
	{

	}

	/**
	 * @brief Runs when an event is triggered.
	 * @param p_Event The event being triggered.
	 */
	void Application::OnEvent(Event& p_Event)
	{
		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		VT_CORE_TRACE("{0}", p_Event);
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

	/**
	 * @brief Runs when the window close event is triggered.
	 * @param p_Event The window close event information.
	 * @returns The successful execution of the event.
	 */
	bool Application::OnWindowClose(WindowCloseEvent& p_Event)
	{
		m_Running = false;
		return true;
	}
}