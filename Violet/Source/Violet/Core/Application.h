/////////////////
///
/// Application.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 1st, 2022
///
/// Contains class information for the application
/// interfacing between a Violet Engine Application
/// and the user or engine defined application.
///
/// The object contains the necessities for a main
/// run loop.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_APPLICATION_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_APPLICATION_H_INCLUDED__

#include "Violet/Core/Core.h"
#include "Violet/Core/Window.h"
#include "Violet/Events/ApplicationEvent.h"
#include "Violet/Events/Event.h"

namespace Violet
{
	/**
	 * @brief Defines the functionality for an Application.
	 */
	class VIOLET_API Application
	{
	public: // Constructors & Deconstructors
		Application();
		virtual ~Application();
	public: // Main Functionality
		void Run();
		void OnEvent(Event& p_Event);
	private: // Event Callback
		bool OnWindowClose(WindowCloseEvent& p_Event);
	private: // Private Member Variables
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/**
	 * @brief A function defined on the Client.
	 * @return The application the Client is returning.
	 */
	Application* CreateApplication();
}

#endif // __VIOLET_ENGINE_CORE_APPLICATION_H_INCLUDED__