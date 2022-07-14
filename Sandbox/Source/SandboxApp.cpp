/////////////////
///
/// SandboxApp.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 13th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include <Violet.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Violet::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray = Violet::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Violet::VertexBuffer> vertexBuffer;
		vertexBuffer = Violet::VertexBuffer::Create(vertices, sizeof(vertices));
		vertexBuffer->SetLayout({
			{ Violet::ShaderDataType::Float3, "a_Position" },
			{ Violet::ShaderDataType::Float4, "a_Color" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Violet::IndexBuffer> indexBuffer;
		indexBuffer = Violet::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = Violet::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Violet::VertexBuffer> squareVB;
		squareVB = Violet::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Violet::ShaderDataType::Float3, "a_Position" },
			{ Violet::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Violet::IndexBuffer> squareIB;
		squareIB = Violet::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		m_Shader = Violet::Shader::Create(vertexSrc, fragmentSrc);

		std::string flatColorVertexSrc = R"(
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

		std::string flatColorFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Violet::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc);

		m_TextureShader = Violet::Shader::Create("Assets/Shaders/Texture.glsl");

		m_Texture = Violet::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_Rainbow = Violet::Texture2D::Create("Assets/Textures/Rainbow.png");

		std::dynamic_pointer_cast<Violet::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Violet::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Violet::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Violet::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Violet::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_Rainbow->Bind();
		Violet::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Violet::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Violet::Event& p_Event) override
	{
		
	}
private:
	Violet::Ref<Violet::Shader> m_Shader;
	Violet::Ref<Violet::VertexArray> m_VertexArray;

	Violet::Ref<Violet::Shader> m_FlatColorShader, m_TextureShader;
	Violet::Ref<Violet::VertexArray> m_SquareVA;

	Violet::Ref<Violet::Texture2D> m_Texture, m_Rainbow;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

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