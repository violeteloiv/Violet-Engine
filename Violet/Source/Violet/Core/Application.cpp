/////////////////
///
/// Application.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 12th, 2022
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
	// Bind Event Function Macro
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	// Insantiate Application Instance
	Application* Application::s_Instance = nullptr;

	/**
	 * @brief Constructs an Application object.
	 */
	Application::Application()
	{
		VT_CORE_ASSERT(!s_Instance, "Application Already Exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Create & Push ImGui Layer.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	/**
	 * @brief Pushes a layer to the LayerStack.
	 * @param p_Layer The layer to be pushed.
	 */
	void Application::PushLayer(Layer* p_Layer)
	{
		m_LayerStack.PushLayer(p_Layer);
	}

	/**
	 * @brief Pushes an overlay to the LayerStack.
	 * @param p_Overlay The overlay to be pushed.
	 */
	void Application::PushOverlay(Layer* p_Overlay)
	{
		m_LayerStack.PushOverlay(p_Overlay);
	}

	/**
	 * @brief Runs when an event is triggered.
	 * @param p_Event The event being triggered.
	 */
	void Application::OnEvent(Event& p_Event)
	{
		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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
		while (m_Running)
		{
			// Delta Time
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			// Update Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			// Every ImGuiLayer gets rendered as part of the ImGui Layer.
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

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