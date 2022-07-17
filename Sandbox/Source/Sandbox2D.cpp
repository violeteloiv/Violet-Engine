/////////////////
///
/// Sandbox2D.cpp
/// Violet McAllister
/// July 14th, 2022
/// Updated: July 17th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include "Sandbox2D.h"

#include <imgui/imgui.h>

#include <typeinfo>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Sandbox2D::OnAttach()
{
	VT_PROFILE_FUNCTION();

	m_CheckerboardTexture = Violet::Texture2D::Create("Assets/Textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	VT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Violet::Timestep p_Timestep)
{
	VT_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(p_Timestep);

	// Render Prep
	{
		VT_PROFILE_SCOPE("Renderer Prep");

		Violet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Violet::RenderCommand::Clear();
	}

	static float rotation = 0.0f;

	Violet::Renderer2D::ResetStats();
	{
		static float rotation = 0.0f;
		rotation += p_Timestep * 50.0f;

		VT_PROFILE_SCOPE("Renderer Draw");

		Violet::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Violet::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Violet::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Violet::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Violet::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Violet::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);

		Violet::Renderer2D::EndScene();

		Violet::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Violet::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Violet::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	VT_PROFILE_FUNCTION();

	auto stats = Violet::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Violet::Event& p_Event)
{
	m_CameraController.OnEvent(p_Event);
}