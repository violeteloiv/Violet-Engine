/////////////////
///
/// OpenGLBuffer.h
/// Violet McAllister
/// July 11th, 2022
///
/// Contains OpenGL implementations of Vertex & 
/// Index Buffer objects used to store information 
/// regarding the vertices and order in which the 
/// vertices are to be drawn in order to avoid overdrawing.
///
/////////////////

#ifndef __VIOLET_ENGINE_OPEN_GL_BUFFER_H_INCLUDED__
#define __VIOLET_ENGINE_OPEN_GL_BUFFER_H_INCLUDED__

#include "Violet/Renderer/Buffer.h"

namespace Violet
{
	/**
	 * @brief 
	 */
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public: // Constructors & Deconstructors
		OpenGLVertexBuffer(float* p_Vertices, uint32_t p_Size);
		virtual ~OpenGLVertexBuffer();
	public: // Main Functionality
		virtual void Bind() const override;
		virtual void Unbind() const override;
	public: // Buffer Layout
		/**
		 * @brief Gets the buffer layout.
		 * @returns The buffer layout.
		 */
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		/**
		 * @brief Sets the buffer layout.
		 * @returns The buffer layout.
		 */
		virtual void SetLayout(const BufferLayout& p_Layout) override { m_Layout = p_Layout; }
	private: // Private Member Variables
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	/**
	 * @brief 
	 */
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public: // Constructors & Deconstructors
		OpenGLIndexBuffer(uint32_t* p_Indices, uint32_t p_Count);
		virtual ~OpenGLIndexBuffer();
	public: // Main Functionality
		virtual void Bind() const;
		virtual void Unbind() const;
	public: // Getters
		/**
		 * @brief Gets the index count.
		 * @returns The index count.
		 */
		virtual uint32_t GetCount() const { return m_Count; }
	private: // Private Member Variables
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}

#endif // __VIOLET_ENGINE_OPEN_GL_BUFFER_H_INCLUDED__