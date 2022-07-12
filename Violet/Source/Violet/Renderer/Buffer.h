/////////////////
///
/// Buffer.h
/// Violet McAllister
/// July 11th, 2022
///
/// Contains Vertex & Index Buffer objects used
/// to store information regarding the vertices
/// and order in which the vertices are to be
/// drawn in order to avoid overdrawing.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_BUFFER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_BUFFER_H_INCLUDED__

namespace Violet
{
	/**
	 * @brief 
	 */
	class VertexBuffer
	{
	public: // Deconstructor
		virtual ~VertexBuffer() = default;
	public: // Main Functionality
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public: // Creator
		static VertexBuffer* Create(float* p_Vertices, uint32_t p_Size);
	};

	/**
	 * @brief 
	 */
	class IndexBuffer
	{
	public: // Deconstructor
		virtual ~IndexBuffer() = default;
	public: // Main Functionality
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public: // Getter
		virtual uint32_t GetCount() const = 0;
	public: // Creator
		static IndexBuffer* Create(uint32_t* p_Indices, uint32_t p_Size);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_BUFFER_H_INCLUDED__