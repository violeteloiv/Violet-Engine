/////////////////
///
/// RendererAPI.cpp
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
/// 
/// Defines functions that are required from
/// all render APIs.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Violet
{
	// Sets the current API to OpenGL.
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	/**
	 * @brief Creates a RendererAPI object based on the current API.
	 */
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}