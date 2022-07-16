/////////////////
///
/// Buffer.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
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
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	/**
	 * @brief Converts the ShaderData Type into the size of the type.
	 * @returns The size of the specified type.
	 */
	static uint32_t ShaderDataTypeSize(ShaderDataType p_Type)
	{
		switch (p_Type)
		{
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		}

		VT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	/**
	 * @brief An element of a buffer.
	 */
	struct BufferElement
	{
	public: // Public Member Variables
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		size_t Offset;
		bool Normalized;
	public: // Constructors
		BufferElement() = default;

		/**
		 * @brief Constructs a BufferElement based on type, name, and normalization.
		 */
		BufferElement(ShaderDataType p_Type, const std::string& p_Name, bool p_Normalized = false)
			: Name(p_Name), Type(p_Type), Size(ShaderDataTypeSize(p_Type)), Offset(0), Normalized(p_Normalized)
		{

		}
	public: // Getters
		/**
		 * @brief Gets the component count based on the shader data type.
		 * @returns The componenet count.
		 */
		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3; // 3 * float3
				case ShaderDataType::Mat4:    return 4; // 4 * float4
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			}

			VT_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	/**
	 * @brief The buffer layout describes what is in a vertex.
	 * Vertices can contain more than just position data, they
	 * can include color, texture coord, etc.
	 */
	class BufferLayout
	{
	public: // Constructors
		BufferLayout() = default;

		/**
		 * @brief Constructs a BufferLayout object using a list of elements.
		 * @param p_Elements The list of elements.
		 */
		BufferLayout(const std::initializer_list<BufferElement>& p_Elements)
			: m_Elements(p_Elements)
		{
			CalculateOffsetsAndStride();
		}
	public: // Getters
		/**
		 * @brief Gets the stride of the layout.
		 * returns The stride of the layout.
		 */
		uint32_t GetStride() const { return m_Stride; }

		/**
		 * @brief Gets the elements in the layout.
		 * @returns The elements in the layout.
		 */
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
	public: // vector overrides
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private: // Helper
		/**
		 * @brief Calculates the Offsets and Stride of an element
		 * and buffer layout.
		 */
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private: // Private Member Variables
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	/**
	 * @brief Contains Vertex information for OpenGL
	 */
	class VertexBuffer
	{
	public: // Deconstructor
		virtual ~VertexBuffer() = default;
	public: // Main Functionality
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* p_Data, uint32_t p_Size) = 0;
	public: // BufferLayout
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& p_Layout) = 0;
	public: // Creators
		static Ref<VertexBuffer> Create(uint32_t p_Size);
		static Ref<VertexBuffer> Create(float* p_Vertices, uint32_t p_Size);
	};

	/**
	 * @brief Contsins Index information for OpenGL.
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
		static Ref<IndexBuffer> Create(uint32_t* p_Indices, uint32_t p_Count);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_BUFFER_H_INCLUDED__