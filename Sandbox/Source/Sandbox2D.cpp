/////////////////
///
/// Sandbox2D.cpp
/// Violet McAllister
/// July 14th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Violet::Timestep p_Timestep)
{
	// Update
	m_CameraController.OnUpdate(p_Timestep);

	// Render
	Violet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Violet::RenderCommand::Clear();

	Violet::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Violet::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });

	Violet::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Violet::Event& p_Event)
{
	m_CameraController.OnEvent(p_Event);
}