/////////////////
///
/// OpenGLRendererAPI.h
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
/// 
/// Implements functions required for all
/// graphics APIs for OpenGL.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_RENDERER_API_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_RENDERER_API_H_INCLUDED__

#include "Violet/Renderer/RendererAPI.h"

namespace Violet
{
	/**
	 * @brief OpenGL implementation of a RendererAPI. 
	 */
	class OpenGLRendererAPI : public RendererAPI
	{
	public: // Initializer
		virtual void Init() override;
	public: // Main Functionality
		virtual void SetViewport(uint32_t p_X, uint32_t p_Y, uint32_t p_Width, uint32_t p_Height) override;
		virtual void SetClearColor(const glm::vec4& p_Color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& p_VertexArray, uint32_t p_IndexCount = 0) override;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_RENDERER_API_H_INCLUDED__