/////////////////
///
/// OpenGLTexture.cpp
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 15th, 2022
///
/// A texture is a collection of
/// data which can be uploaded to
/// the GPU and processed as an
/// image.
/// 
/// The OpenGL Implementation.
///
/////////////////

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include <stb_image.h>

namespace Violet
{
	/**
	 * @brief Constructs an OpenGLTexture2D object using only the
	 * width and height that the texture should be.
	 * @param p_Width The width of the created texture.
	 * @param p_Height The height of the created texture.
	 */
	OpenGLTexture2D::OpenGLTexture2D(uint32_t p_Width, uint32_t p_Height)
		: m_Width(p_Width), m_Height(p_Height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	/**
	 * @brief Constructs an OpenGLTexture2D object. 
	 * @param p_Filepath The path to the image file.
	 */
	OpenGLTexture2D::OpenGLTexture2D(const std::string& p_Filepath)
		: m_Path(p_Filepath)
	{
		// Get The Width, Height, and Channels
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		// Get image data
		stbi_uc* data = stbi_load(p_Filepath.c_str(), &width, &height, &channels, 0);
		VT_CORE_ASSERT(data, "[STB_IMAGE ERROR] Failed To Load Image!");
		m_Width = width;
		m_Height = height;

		// Determine Internal & Data Formats
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		// Create texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		// Image Renderering Settings
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		// Free the image data
		stbi_image_free(data);
	}

	/**
	 * @brief Deconstructs an OpenGLTexture2D object. 
	 */
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* p_Data, uint32_t p_Size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		VT_CORE_ASSERT(p_Size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, p_Data);
	}

	/**
	 * @brief Binds the image to a specific slot in the GPU.
	 * @param p_Slot The slot in the GPU.
	 */
	void OpenGLTexture2D::Bind(uint32_t p_Slot) const
	{
		glBindTextureUnit(p_Slot, m_RendererID);
	}
}