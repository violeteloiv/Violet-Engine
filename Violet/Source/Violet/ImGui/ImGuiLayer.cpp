/////////////////
///
/// ImGuiLayer.cpp
/// Violet McAllister
/// July 11th, 2022
///
/// Defines the implementation for an ImGuiLayer.
///
/////////////////

#include "vtpch.h"

#include "Violet/ImGui/ImGuiLayer.h"

#include <imgui.h>

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Violet/Core/Application.h"

namespace Violet
{
	/**
	 * @brief Runs when the layer is attached to the layerstack.
	 */
	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	/**
	 * @brief Runs when the layer is detached from the layerstack. 
	 */
	void ImGuiLayer::OnDetach()
	{

	}

	/**
	 * @brief Runs when the layer is updated.
	 */
	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		// Define the size of the display for ImGui
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Determine DeltaTime for ImGui
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Initialize
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	/**
	 * Runs when an event is triggered in the layer. 
	 */
	void ImGuiLayer::OnEvent(Event& p_Event)
	{
		EventDispatcher dispatcher(p_Event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(VT_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	/**
	 * @brief Runs when the mouse button is pressed.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		// Sets the mouse button to true.
		io.MouseDown[p_Event.GetMouseButton()] = true;

		return false;
	}

	/**
	 * @brief Runs when the mouse button is released.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		// Sets the mouse button to false.
		io.MouseDown[p_Event.GetMouseButton()] = false;

		return false;
	}

	/**
	 * @brief Runs when the mouse is moved.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(p_Event.GetX(), p_Event.GetY());

		return false;
	}

	/**
	 * @brief Runs when the mouse is scrolled.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += p_Event.GetXOffset();
		io.MouseWheel += p_Event.GetYOffset();

		return false;
	}

	/**
	 * @brief Runs when a key is pressed.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[p_Event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	/**
	 * @brief Runs when a key is released.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[p_Event.GetKeyCode()] = false;

		return false;
	}

	/**
	 * @brief Runs when a key is typed.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = p_Event.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	/**
	 * @brief Runs when the window is resized.
	 * @param p_Event the event information.
	 * @returns The success of the event.
	 */
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(p_Event.GetWidth(), p_Event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, p_Event.GetWidth(), p_Event.GetHeight());

		return false;
	}
}