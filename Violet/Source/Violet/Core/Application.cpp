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

#include <glad/glad.h>

#include "Violet/Core/Application.h"
#include "Violet/Core/Input.h"
#include "Violet/Core/Log.h"

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

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Create & Push ImGui Layer.
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Initialize Triangle Renderering

		// Vertex Array Generation
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		// Vertex Buffer Generation
		glGenBuffers(1, &m_VertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		
		// Vertex Data
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		// Assign Data To The Vertex Buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Enable Vertex Array
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// Generate Index Buffer
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		// Assign Index Buffer Data
		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Destructs an Application object.
	 */
	Application::~Application()
	{

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
			// Sets what the window should clear to.
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			// Clears the screen of pixels.
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw Triangle
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			// Update Layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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