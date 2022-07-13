/////////////////
///
/// Renderer.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 12th, 2022
///
/// Violet's main renderer which handles
/// creating and ending a scene, as well
/// as drawing from Vertex Arrays.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_H_INCLUDED__

#include "Violet/Renderer/OrthographicCamera.h"
#include "Violet/Renderer/RenderCommand.h"
#include "Violet/Renderer/Shader.h"

namespace Violet
{
	/**
	 * @brief Defines information about a Renderer.
	 */
	class Renderer
	{
	public: // Main Functionality
		static void BeginScene(OrthographicCamera& p_Camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& p_Shader, const std::shared_ptr<VertexArray>& p_VertexArray);
	public: // Getter
		/**
		 * @brief Gets the Renderer API.
		 * @returns The Renderer API.
		 */
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private: // SceneData
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	private: // Private Static Member Variables
		static SceneData* s_SceneData;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_H_INCLUDED__