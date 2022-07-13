/////////////////
///
/// 
/// VertexArray.cpp
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 13th, 2022
///
/// The vertex array object contains
/// information about how the vertex 
/// attributes (position, color, etc.)
/// are stored in a vertex buffer.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	/**
	 * @brief Creates a VertexArray object based on the current API.
	 */
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}