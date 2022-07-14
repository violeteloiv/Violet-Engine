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
	m_SquareVA = Violet::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Violet::Ref<Violet::VertexBuffer> squareVB;
	squareVB = Violet::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Violet::ShaderDataType::Float3, "a_Position" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Violet::Ref<Violet::IndexBuffer> squareIB;
	squareIB = Violet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Violet::Shader::Create("assets/shaders/FlatColor.glsl");
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

	Violet::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Violet::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Violet::Renderer::EndScene();
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