/////////////////
///
/// Application.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 16th, 2022
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

#include "Violet/Core/Base.h"
#include "Violet/Core/Layer.h"
#include "Violet/Core/LayerStack.h"
#include "Violet/Core/Timestep.h"
#include "Violet/Core/Window.h"
#include "Violet/Events/ApplicationEvent.h"
#include "Violet/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Violet
{
	/**
	 * @brief Defines the functionality for an Application.
	 */
	class Application
	{
	public: // Constructors & Deconstructors
		Application();
		virtual ~Application();
	public: // Main Functionality
		void OnEvent(Event& p_Event);
		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);
		void Close();
	public: // Getters & Setters
		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
	private: // Event Callback
		bool OnWindowClose(WindowCloseEvent& p_Event);
		bool OnWindowResize(WindowResizeEvent& p_Event);
	private: // Private Functionality
		void Run();
	private: // Private Member Variables
		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private: // Static Instance
		static Application* s_Instance;
	private: // Friend Objects
		friend int ::main(int argc, char** argv);
	};

	/**
	 * @brief A function defined on the Client.
	 * @return The application the Client is returning.
	 */
	Application* CreateApplication();
}

#endif // __VIOLET_ENGINE_CORE_APPLICATION_H_INCLUDED__