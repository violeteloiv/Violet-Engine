/////////////////
///
/// ImGuiLayer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
///
/// Defines the implementation for an ImGuiLayer.
///
/////////////////

#include "vtpch.h"

#include "Violet/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Violet/Core/Application.h"

namespace Violet
{
	/**
	 * @brief Runs when the layer is attached to the layerstack.
	 */
	void ImGuiLayer::OnAttach()
	{
		VT_PROFILE_FUNCTION();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	/**
	 * @brief Runs when the layer is detached from the layerstack. 
	 */
	void ImGuiLayer::OnDetach()
	{
		VT_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	/**
	 * @brief Forces ImGui to capture Mouse & Keyboard events
	 * @param p_Event The event info.
	 */
	void ImGuiLayer::OnEvent(Event& p_Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		p_Event.Handled |= p_Event.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		p_Event.Handled |= p_Event.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}

	/**
	 * @brief Begins an ImGui context.
	 */
	void ImGuiLayer::Begin()
	{
		VT_PROFILE_FUNCTION();

		// Initialize
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	/**
	 * @brief Ends an ImGui context.
	 */
	void ImGuiLayer::End()
	{
		VT_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}