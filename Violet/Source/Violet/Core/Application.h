/////////////////
///
/// Application.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 11th, 2022
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
#include "Violet/Core/Layer.h"
#include "Violet/Core/LayerStack.h"
#include "Violet/Core/Window.h"
#include "Violet/Events/ApplicationEvent.h"
#include "Violet/ImGui/ImGuiLayer.h"
#include "Violet/Renderer/Buffer.h"
#include "Violet/Renderer/Shader.h"

namespace Violet
{
	/**
	 * @brief Defines the functionality for an Application.
	 */
	class Application
	{
	public: // Constructors & Deconstructors
		Application();
		virtual ~Application() = default;
	public: // Main Functionality
		void Run();
		void OnEvent(Event& p_Event);
		void PushLayer(Layer* p_Layer);
		void PushOverlay(Layer* p_Overlay);
	public: // Getters & Setters
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private: // Event Callback
		bool OnWindowClose(WindowCloseEvent& p_Event);
	private: // Private Member Variables
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
	private: // Renderer Specific
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private: // Static Instance
		static Application* s_Instance;
	};

	/**
	 * @brief A function defined on the Client.
	 * @return The application the Client is returning.
	 */
	Application* CreateApplication();
}

#endif // __VIOLET_ENGINE_CORE_APPLICATION_H_INCLUDED__