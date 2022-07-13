/////////////////
///
/// OpenGLTexture.cpp
/// Violet McAllister
/// July 13th, 2022
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

#include <glad/glad.h>

#include <stb_image.h>

namespace Violet
{
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

		// Create texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

		// Image Renderering Settings
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

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

	/**
	 * @brief Binds the image to a specific slot in the GPU.
	 * @param p_Slot The slot in the GPU.
	 */
	void OpenGLTexture2D::Bind(uint32_t p_Slot) const
	{
		glBindTextureUnit(p_Slot, m_RendererID);
	}
}