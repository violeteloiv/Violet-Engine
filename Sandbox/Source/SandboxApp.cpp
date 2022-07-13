/////////////////
///
/// SandboxApp.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 11th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include <Violet.h>

#include <imgui/imgui.h>

class ExampleLayer : public Violet::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Violet::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Violet::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Violet::VertexBuffer::Create(vertices, sizeof(vertices)));
		Violet::BufferLayout layout = {
			{ Violet::ShaderDataType::Float3, "a_Position" },
			{ Violet::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Violet::IndexBuffer> indexBuffer;
		indexBuffer.reset(Violet::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Violet::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Violet::VertexBuffer> squareVB;
		squareVB.reset(Violet::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Violet::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Violet::IndexBuffer> squareIB;
		squareIB.reset(Violet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Violet::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Violet::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Violet::Timestep p_Timestep) override
	{
		if (Violet::Input::IsKeyPressed(VT_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * p_Timestep;
		else if (Violet::Input::IsKeyPressed(VT_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * p_Timestep;

		if (Violet::Input::IsKeyPressed(VT_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * p_Timestep;
		else if (Violet::Input::IsKeyPressed(VT_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * p_Timestep;

		if (Violet::Input::IsKeyPressed(VT_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * p_Timestep;
		if (Violet::Input::IsKeyPressed(VT_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * p_Timestep;

		Violet::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Violet::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Violet::Renderer::BeginScene(m_Camera);

		Violet::Renderer::Submit(m_BlueShader, m_SquareVA);
		Violet::Renderer::Submit(m_Shader, m_VertexArray);

		Violet::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Text");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Violet::Event& p_Event) override
	{
		
	}
private:
	std::shared_ptr<Violet::Shader> m_Shader;
	std::shared_ptr<Violet::VertexArray> m_VertexArray;

	std::shared_ptr<Violet::Shader> m_BlueShader;
	std::shared_ptr<Violet::VertexArray> m_SquareVA;

	Violet::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class SandboxApp : public Violet::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};

Violet::Application* Violet::CreateApplication()
{
	return new SandboxApp();
}