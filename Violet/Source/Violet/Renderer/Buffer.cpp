/////////////////
///
/// Buffer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 13th, 2022
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
	/**
	 * @brief Creates a VertexBuffer object based on the current API.
	 * @param p_Vertices The vertices to be added to the vertex buffer.
	 * @param p_Size The size of the vertices.
	 */
	Ref<VertexBuffer> VertexBuffer::Create(float* p_Vertices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(p_Vertices, p_Size);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	/**
	 * @brief Creates an IndexBuffer object based on the current API.
	 * @param p_Indices The indices to be added to the index buffer.
	 * @param p_Size The count of the indices.
	 */
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* p_Indices, uint32_t p_Size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(p_Indices, p_Size);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}