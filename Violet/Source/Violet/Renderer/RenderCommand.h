/////////////////
///
/// RenderCommand.h
/// Violet McAllister
/// July 12th, 2022
///
/// Abstracts away referencing a
/// specific RendererAPI.
/// 
/// Main form of communication between
/// Violet and graphics APIs.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_RENDER_COMMAND_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_RENDER_COMMAND_H_INCLUDED__

#include "Violet/Renderer/RendererAPI.h"

namespace Violet
{
	class RenderCommand
	{
	public: // Main Functionality
		/**
		 * @brief Sets the background color that gets
		 * cleared to when the window is cleared before
		 * renderering.
		 * @param p_Color The background color.
		 */
		inline static void SetClearColor(const glm::vec4& p_Color)
		{
			s_RendererAPI->SetClearColor(p_Color);
		}

		/**
		 * @brief Clears the window before renderering.
		 */
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		/**
		 * @brief Draws the data in the Vertex Array.
		 * @param p_VertexArray The Vertex Array.
		 */
		inline static void DrawIndexed(const Ref<VertexArray>& p_VertexArray)
		{
			s_RendererAPI->DrawIndexed(p_VertexArray);
		}
	private: // Private State Member Variables
		static RendererAPI* s_RendererAPI;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_RENDER_COMMAND_H_INCLUDED__