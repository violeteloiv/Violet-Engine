/////////////////
///
/// Application.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 15th, 2022
///
/// Contains class implementations for the Application
/// object.
///
/////////////////

#include "vtpch.h"

#include <GLFW/glfw3.h>

#include "Violet/Core/Application.h"
#include "Violet/Core/Input.h"
#include "Violet/Core/Log.h"
#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	// Insantiate Application Instance
	Application* Application::s_Instance = nullptr;

	/**
	 * @brief Constructs an Application object.
	 */
	Application::Application()
	{
		VT_PROFILE_FUNCTION();

		VT_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(VT_BIND_EVENT_FN(Application::OnEvent));

		// Initialize Violet Subsystems
		Renderer::Init();

		// Create & Push ImGui Layer.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	/**
	 * @brief Deconstructs an Application object. 
	 */
	Application::~Application()
	{
		VT_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	/**
	 * @brief Pushes a layer to the LayerStack.
	 * @param p_Layer The layer to be pushed.
	 */
	void Application::PushLayer(Layer* p_Layer)
	{
		VT_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(p_Layer);
		p_Layer->OnAttach();
	}

	/**
	 * @brief Pushes an overlay to the LayerStack.
	 * @param p_Overlay The overlay to be pushed.
	 */
	void Application::PushOverlay(Layer* p_Overlay)
	{
		VT_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(p_Overlay);
		p_Overlay->OnAttach();
	}

	/**
	 * @brief Runs when an event is triggered.
	 * @param p_Event The event being triggered.
	 */
	void Application::OnEvent(Event& p_Event)
	{
		VT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<WindowCloseEvent>(VT_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(VT_BIND_EVENT_FN(Application::OnWindowResize));

		// Loop through the LayerStack and look for OnEvent functions.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(p_Event);
			if (p_Event.Handled)
				break;
		}
	}

	/**
	 * @brief Contains the main run loop and handles updating the application.
	 */
	void Application::Run()
	{
		VT_PROFILE_FUNCTION();

		while (m_Running)
		{
			VT_PROFILE_SCOPE("RunLoop")

			// Delta Time
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Update Layers
			if (!m_Minimized)
			{
				{
					VT_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				// Every ImGuiLayer gets rendered as part of the ImGui Layer.
				m_ImGuiLayer->Begin();
				{
					VT_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

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

	/**
	 * @brief Runs when the window is resized.
	 * @param p_Event The window resize event information.
	 * @returns The successful execution of the event.
	 */
	bool Application::OnWindowResize(WindowResizeEvent& p_Event)
	{
		VT_PROFILE_FUNCTION();

		if (p_Event.GetWidth() == 0 || p_Event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(p_Event.GetWidth(), p_Event.GetHeight());

		return false;
	}
}