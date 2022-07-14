/////////////////
///
/// Renderer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 13th, 2022
///
/// Violet's main renderer which handles
/// creating and ending a scene, as well
/// as drawing from Vertex Arrays.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Violet
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	/**
	 * @brief Initializes the renderer. 
	 */
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	/**
	 * @brief Runs when the window is resized.
	 * @param p_Width The width the window is resized to.
	 * @param p_Height The height the window is resized to.
	 */
	void Renderer::OnWindowResize(uint32_t p_Width, uint32_t p_Height)
	{
		RenderCommand::SetViewport(0, 0, p_Width, p_Height);
	}

	/**
	 * @brief Initializes for the scene. 
	 * @param p_Camera The camera being initialized.
	 */
	void Renderer::BeginScene(OrthographicCamera& p_Camera)
	{
		s_SceneData->ViewProjectionMatrix = p_Camera.GetViewProjectionMatrix();
	}

	/**
	 * @brief Shutdowns the scene.   
	 */
	void Renderer::EndScene()
	{

	}

	/**
	 * @brief Submits a vertex array to be rendered with a shader.
	 * @param p_Shader The shader to be bound.
	 * @param p_VertexArray The vertex array to be submitted.
	 */
	void Renderer::Submit(const Ref<Shader>& p_Shader, const Ref<VertexArray>& p_VertexArray, const glm::mat4& p_Transform)
	{
		p_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(p_Shader)->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(p_Shader)->UploadUniformMat4("u_Transform", p_Transform);

		p_VertexArray->Bind();
		RenderCommand::DrawIndexed(p_VertexArray);
	}
}