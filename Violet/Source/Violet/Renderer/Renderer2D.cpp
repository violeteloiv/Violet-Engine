/////////////////
///
/// Renderer2D.cpp
/// Violet McAllister
/// July 14th, 2022
/// Updated: July 15th, 2022
///
/// Violet's main 2D Renderer which
/// handles drawing 2D shapes.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>

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
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
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
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		// Create Index Buffer
		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		// Create Default Texture
		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		// Texture Shader
		s_Data->TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
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
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", p_Camera.GetViewProjectionMatrix());
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
		s_Data->TextureShader->SetFloat4("u_Color", p_Color);
		s_Data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a texture.
	 * @param p_Position The 2D position.
	 * @param p_Size The size of the square.
	 * @param p_Texture The texture for the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture)
	{
		DrawQuad({ p_Position.x, p_Position.y, 0.0f }, p_Size, p_Texture);
	}

	/**
	 * @brief Draws a square at a position, with a size, and with a texture.
	 * @param p_Position The 3D position.
	 * @param p_Size The size of the square.
	 * @param p_Texture The texture for the square.
	 */
	void Renderer2D::DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture)
	{
		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		p_Texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), p_Position) * glm::scale(glm::mat4(1.0f), { p_Size.x, p_Size.y, 1.0f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}