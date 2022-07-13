/////////////////
///
/// OpenGLTexture.h
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

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__

#include "Violet/Renderer/Texture.h"

namespace Violet
{
	/**
	 * @brief OpenGL Implementation of a 2D Texture object. 
	 */
	class OpenGLTexture2D : public Texture2D
	{
	public: // Constructors & Deconstructors
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
	public: // Main Functionality
		virtual void Bind(uint32_t p_Slot = 0) const override;
	private: // Private Member Variables
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_TEXTURE_H_INCLUDED__