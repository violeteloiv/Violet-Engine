/////////////////
///
/// Renderer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 12th, 2022
///
/// Violet's main renderer which handles
/// creating and ending a scene, as well
/// as drawing from Vertex Arrays.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

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
	void Renderer::Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray)
	{
		p_Shader->Bind();
		p_Shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		p_VertexArray->Bind();
		RenderCommand::DrawIndexed(p_VertexArray);
	}
}