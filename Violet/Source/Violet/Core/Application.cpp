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

	}

	/**
	 * @brief Destructs an Application object.
	 */
	Application::~Application()
	{

	}

	/**
	 * @brief Contains the main run loop.
	 */
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			VT_TRACE(e);
		if (e.IsInCategory(EventCategoryInput))
			VT_TRACE(e);

		while (true);
	}
}