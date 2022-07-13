/////////////////
///
/// Application.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 12th, 2022
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
#include "Violet/Renderer/OrthographicCamera.h"
#include "Violet/Renderer/Shader.h"
#include "Violet/Renderer/VertexArray.h"

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
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
		OrthographicCamera m_Camera;
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