/////////////////
///
/// ExampleLayer.cpp
/// Violet McAllister
/// July 15th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include "ExampleLayer.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Violet::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Violet::Ref<Violet::VertexBuffer> vertexBuffer = Violet::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Violet::ShaderDataType::Float3, "a_Position" },
		{ Violet::ShaderDataType::Float4, "a_Color" }
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Violet::Ref<Violet::IndexBuffer> indexBuffer = Violet::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_SquareVA = Violet::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Violet::Ref<Violet::VertexBuffer> squareVB = Violet::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Violet::ShaderDataType::Float3, "a_Position" },
		{ Violet::ShaderDataType::Float2, "a_TexCoord" }
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Violet::Ref<Violet::IndexBuffer> squareIB = Violet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
		#version 330 core
			
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		}
	)";

	std::string fragmentSrc = R"(
		#version 330 core
			
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
		in vec4 v_Color;

		void main()
		{
			color = vec4(v_Position * 0.5 + 0.5, 1.0);
			color = v_Color;
		}
	)";

	m_Shader = Violet::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

	std::string flatColorShaderVertexSrc = R"(
		#version 330 core
			
		layout(location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;

		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
		}
	)";

	std::string flatColorShaderFragmentSrc = R"(
		#version 330 core
			
		layout(location = 0) out vec4 color;

		in vec3 v_Position;
			
		uniform vec3 u_Color;

		void main()
		{
			color = vec4(u_Color, 1.0);
		}
	)";

	m_FlatColorShader = Violet::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

	auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

	m_Texture = Violet::Texture2D::Create("Assets/Textures/Checkerboard.png");
	m_ChernoLogoTexture = Violet::Texture2D::Create("Assets/Textures/ChernoLogo.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Violet::Timestep p_Timestep)
{
	// Update
	m_CameraController.OnUpdate(p_Timestep);

	// Render
	Violet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Violet::RenderCommand::Clear();

	Violet::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Violet::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Violet::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Violet::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Violet::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Violet::Event& p_Event)
{
	m_CameraController.OnEvent(p_Event);
}