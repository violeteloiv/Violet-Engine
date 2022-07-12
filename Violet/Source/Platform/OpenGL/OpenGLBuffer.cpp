/////////////////
///
/// OpenGLBuffer.cpp
/// Violet McAllister
/// July 11th, 2022
///
/// Contains OpenGL implementations of Vertex & 
/// Index Buffer objects used to store information 
/// regarding the vertices and order in which the 
/// vertices are to be drawn in order to avoid overdrawing.
///
/////////////////

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Violet
{
	/////////////////////////////
	// VertexBuffer /////////////
	/////////////////////////////

	/**
	 * @brief Constructs an OpenGLVertexBuffer object.
	 * @param p_Vertices The vertices for the buffer.
	 * @param p_Size The size of the buffer.
	 */
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* p_Vertices, uint32_t p_Size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, p_Vertices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Deconstructs an OpenGLVertexBuffer object. 
	 */
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	/**
	 * @brief Binds the Vertex Buffer. 
	 */
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * @brief Unbinds the Vertex Buffer.
	 */
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/////////////////////////////
	// IndexBuffer //////////////
	/////////////////////////////

	/**
	 * @brief Constructs an OpenGLIndexBuffer object.
	 * @param p_Indices The indices for the buffer.
	 * @param p_Count The number of indices.
	 */
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* p_Indices, uint32_t p_Count)
		: m_Count(p_Count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_Count * sizeof(uint32_t), p_Indices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Deconstructs an OpenGLIndexBuffer object.
	 */
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	/**
	 * @brief Binds the Index Buffer. 
	 */
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * @brief Unbinds the Index Buffer. 
	 */
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
