/////////////////
///
/// Renderer2D.cpp
/// Violet McAllister
/// July 14th, 2022
///
/// Violet's main 2D Renderer which
/// handles drawing 2D shapes.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Violet/Renderer/RenderCommand.h"
#include "Violet/Renderer/Shader.h"
#include "Violet/Renderer/VertexArray.h"

namespace Violet
{
	/**
	 * @brief Contains data needed to render. 
	 */
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	/**
	 * @brief Initializes the renderer.
	 */
	void Renderer2D::Init()
	{
		// Initialize Data
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		// Create Vertex Buffer & Layout
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		// Create Index Buffer
		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		// Shader
		s_Data->FlatColorShader = Shader::Create("Assets/Shaders/FlatColor.glsl");
	}

	/**
	 * @brief Shuts down the renderer. 
	 */
	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	/**
	 * @brief Begins the scene by updating view projections.
	 * @param p_Camera The camera view.
	 */
	void Renderer2D::BeginScene(const OrthographicCamera& p_Camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	/**
	 * @brief Ends the scene. 
	 */
	void Renderer2D::EndScene()
	{

	}

	/**
	 * @brief Draws a square at a position, with a size, and with a color.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Color the color of the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Color);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a color.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Color the color of the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->UploadUniformFloat4("u_Color", p_Color);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}