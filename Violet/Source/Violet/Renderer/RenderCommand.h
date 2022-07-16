/////////////////
///
/// RenderCommand.h
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
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
		 * @brief Initializes the graphics API. 
		 */
		static void Init()
		{
			s_RendererAPI->Init();
		}

		/**
		 * @brief Sets the viewport size and position.
		 * @param p_X The x position.
		 * @param p_Y The y position.
		 * @param p_Width The width.
		 * @param p_Height The height.
		 */
		static void SetViewport(uint32_t p_X, uint32_t p_Y, uint32_t p_Width, uint32_t p_Height)
		{
			s_RendererAPI->SetViewport(p_X, p_Y, p_Width, p_Height);
		}

		/**
		 * @brief Sets the background color that gets
		 * cleared to when the window is cleared before
		 * renderering.
		 * @param p_Color The background color.
		 */
		static void SetClearColor(const glm::vec4& p_Color)
		{
			s_RendererAPI->SetClearColor(p_Color);
		}

		/**
		 * @brief Clears the window before renderering.
		 */
		static void Clear()
		{
			s_RendererAPI->Clear();
		}

		/**
		 * @brief Draws the data in the Vertex Array.
		 * @param p_VertexArray The Vertex Array.
		 * @param p_Count The index count.
		 */
		static void DrawIndexed(const Ref<VertexArray>& p_VertexArray, uint32_t p_Count = 0)
		{
			s_RendererAPI->DrawIndexed(p_VertexArray, p_Count);
		}
	private: // Private State Member Variables
		static Scope<RendererAPI> s_RendererAPI;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_RENDER_COMMAND_H_INCLUDED__