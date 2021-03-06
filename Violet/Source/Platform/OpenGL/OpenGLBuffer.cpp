/////////////////
///
/// OpenGLBuffer.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
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
	 * @brief Constructs an OpenGLVertexBufer object using
	 * only the size of the buffer.
	 * @param p_Size The size of the buffer.
	 */
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t p_Size)
	{
		VT_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, nullptr, GL_DYNAMIC_DRAW);
	}

	/**
	 * @brief Constructs an OpenGLVertexBuffer object.
	 * @param p_Vertices The vertices for the buffer.
	 * @param p_Size The size of the buffer.
	 */
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* p_Vertices, uint32_t p_Size)
	{
		VT_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, p_Vertices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Deconstructs an OpenGLVertexBuffer object. 
	 */
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		VT_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	/**
	 * @brief Binds the Vertex Buffer. 
	 */
	void OpenGLVertexBuffer::Bind() const
	{
		VT_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * @brief Unbinds the Vertex Buffer.
	 */
	void OpenGLVertexBuffer::Unbind() const
	{
		VT_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/**
	 * @brief Sets the data inside the vertex buffer.
	 * @param p_Data The data to place inside the vertex buffer.
	 * @param p_Size The size of the data.
	 */
	void OpenGLVertexBuffer::SetData(const void* p_Data, uint32_t p_Size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, p_Size, p_Data);
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
		VT_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);

		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, p_Count * sizeof(uint32_t), p_Indices, GL_STATIC_DRAW);
	}

	/**
	 * @brief Deconstructs an OpenGLIndexBuffer object.
	 */
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		VT_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	/**
	 * @brief Binds the Index Buffer. 
	 */
	void OpenGLIndexBuffer::Bind() const
	{
		VT_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * @brief Unbinds the Index Buffer. 
	 */
	void OpenGLIndexBuffer::Unbind() const
	{
		VT_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
