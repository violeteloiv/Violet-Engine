/////////////////
///
/// Buffer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 12th, 2022
///
/// Contains Vertex & Index Buffer objects used
/// to store information regarding the vertices
/// and order in which the vertices are to be
/// drawn in order to avoid overdrawing.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	VertexBuffer* VertexBuffer::Create(float* p_Vertices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(p_Vertices, p_Size);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* p_Indices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(p_Indices, p_Size);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}