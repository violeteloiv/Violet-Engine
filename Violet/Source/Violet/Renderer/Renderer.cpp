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
	/**
	 * @brief Initializes for the scene. 
	 */
	void Renderer::BeginScene()
	{

	}

	/**
	 * @brief Shutdowns the scene.   
	 */
	void Renderer::EndScene()
	{

	}

	/**
	 * @brief Submits a vertex array to be rendered.
	 * @param p_VertexArray The vertex array to be submitted.
	 */
	void Renderer::Submit(const std::shared_ptr<VertexArray>& p_VertexArray)
	{
		p_VertexArray->Bind();
		RenderCommand::DrawIndexed(p_VertexArray);
	}
}