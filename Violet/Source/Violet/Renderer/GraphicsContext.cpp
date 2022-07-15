/////////////////
///
/// GraphicsContext.h
/// Violet McAllister
/// July 15th, 2022
///
/// A graphics context is what the renderer
/// actually displays to. It contains buffers which
/// pixels are drawn to and then displayed.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/GraphicsContext.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	/**
	 * @brief Creates a GraphicsContext object based on the current API.
	 * @param p_Window The window handle for the API.
	 */
	Scope<GraphicsContext> GraphicsContext::Create(void* p_Window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(p_Window));
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}