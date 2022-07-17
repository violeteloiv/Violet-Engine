/////////////////
///
/// OpenGLTexture.h
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

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__

#include <glad/glad.h>

#include "Violet/Renderer/Texture.h"

namespace Violet
{
	/**
	 * @brief OpenGL Implementation of a 2D Texture object. 
	 */
	class OpenGLTexture2D : public Texture2D
	{
	public: // Constructors & Deconstructors
		OpenGLTexture2D(uint32_t p_Width, uint32_t p_Height);
		OpenGLTexture2D(const std::string& p_Filepath);
		virtual ~OpenGLTexture2D();
	public: // Getters
		/**
		 * @brief Gets the width of the texture.
		 * @returns The width of the texture.
		 */
		virtual uint32_t GetWidth() const override { return m_Width; }

		/**
		 * @brief Gets the height of the texture.
		 * @returns The height of the texture.
		 */
		virtual uint32_t GetHeight() const override { return m_Height; }
	public: // Setter
		virtual void SetData(void* p_Data, uint32_t p_Size) override;
	public: // Main Functionality
		virtual void Bind(uint32_t p_Slot = 0) const override;
	public: // Operator Overrides
		virtual bool operator==(const Texture& p_Other) const override
		{
			return m_RendererID == ((OpenGLTexture2D&)p_Other).m_RendererID;
		}
	private: // Private Member Variables
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__