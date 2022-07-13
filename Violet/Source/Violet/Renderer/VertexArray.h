/////////////////
///
/// VertexArray.h
/// Violet McAllister
/// July 12th, 2022
///
/// The vertex array object contains
/// information about how the vertex 
/// attributes (position, color, etc.)
/// are stored in a vertex buffer.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_VERTEX_ARRAY_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_VERTEX_ARRAY_H_INCLUDED__

#include <memory>

#include "Violet/Renderer/Buffer.h"

namespace Violet
{
	/**
	 * @brief Contains definitions for all
	 * Vertex Array functionality.
	 */
	class VertexArray
	{
	public: // Deconstructor
		virtual ~VertexArray() = default;
	public: // Main Functionality
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& p_VertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& p_IndexBuffer) = 0;
	public: // Getters
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
	public: // Creator
		static VertexArray* Create();
	};
}

#endif // __VIOLET_ENGINE_RENDERER_VERTEX_ARRAY_H_INCLUDED__