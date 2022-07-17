/////////////////
///
/// OpenGLVertexArray.cpp
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
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

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Violet
{
	/**
	 * @brief Turns a Violet ShaderType into an OpenGL ShaderType.
	 * @returns The OpenGL Shader Type.
	 */
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType p_Type)
	{
		switch (p_Type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		VT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/**
	 * @brief Constructs an OpenGL Vertex Array. 
	 */
	OpenGLVertexArray::OpenGLVertexArray()
	{
		VT_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	/**
	 * @brief Deconstructs an OpenGL Vertex Array. 
	 */
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		VT_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	/**
	 * @brief Binds a Vertex Array. 
	 */
	void OpenGLVertexArray::Bind() const
	{
		VT_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	/**
	 * @brief Unbinds a Vertex Array. 
	 */
	void OpenGLVertexArray::Unbind() const
	{
		VT_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	/**
	 * @brief Adds a Vertex Buffer to the Vertex Array.
	 * @param p_VertexBuffer The vertex buffer to be added.
	 */
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& p_VertexBuffer)
	{
		VT_PROFILE_FUNCTION();

		VT_CORE_ASSERT(p_VertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer Has No Layout!");

		glBindVertexArray(m_RendererID);
		p_VertexBuffer->Bind();

		const auto& layout = p_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					m_VertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(m_VertexBufferIndex);
						glVertexAttribPointer(m_VertexBufferIndex,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(sizeof(float) * count * i));
						glVertexAttribDivisor(m_VertexBufferIndex, 1);
						m_VertexBufferIndex++;
					}
					break;
				}
				default:
					VT_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(p_VertexBuffer);
	}

	/**
	 * @brief Adds an Index Buffer into the Vertex Array.
	 * @param p_IndexBuffer The index buffer to be added.
	 */
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& p_IndexBuffer)
	{
		VT_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		p_IndexBuffer->Bind();

		m_IndexBuffer = p_IndexBuffer;
	}
}