/////////////////
///
/// OpenGLVertexArray.h
/// Violet McAllister
/// July 12th, 2022
///
/// The vertex array object contains
/// information about how the vertex 
/// attributes (position, color, etc.)
/// are stored in a vertex buffer.
/// 
/// This is an OpenGL Implementation of
/// a Vertex Array.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_VERTEX_ARRAY_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_VERTEX_ARRAY_H_INCLUDED__

#include "Violet/Renderer/VertexArray.h"

namespace Violet
{
	/**
	 * @brief OpenGL Implementation of a
	 * Vertex Array.
	 */
	class OpenGLVertexArray : public VertexArray
	{
	public: // Constructors
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
	public: // Main Functionality
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer) override;
	public: // Getters
		/**
		 * @brief Gets the list of vertex buffers.
		 * @returns The list of vertex buffers.
		 */
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const{ return m_VertexBuffers; }

		/**
		 * @brief Gets the set index buffer.
		 * @returns The set index buffer.
		 */
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private: // Private Member Variables
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_VERTEX_ARRAY_H_INCLUDED__