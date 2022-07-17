/////////////////
///
/// OpenGLFramebuffer.cpp
/// Violet McAllister
/// July 17th, 2022
///
/// A framebuffer contains information
/// about the currently rendered pixels 
/// on the screen to be used for later.
/// 
/// An OpenGL Implementation.
///
/////////////////

#include "vtpch.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Violet
{
	/**
	 * @brief Constructs an OpenGL Framebuffer object with reference
	 * to a specification.
	 */
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& p_Specification)
		: m_Specification(p_Specification)
	{
		Invalidate();
	}

	/**
	 * @brief Deconstructs an OpenGL Framebuffer object. 
	 */
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	/**
	 * @brief Handles the creation and settings of the color
	 * and depth attachments.
	 */
	void OpenGLFramebuffer::Invalidate()
	{
		// If the framebuffer is already defined, delete stuff
		// before reassigning.
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		// Creates a Framebuffer object.
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// Creates the buffer for the pixels.
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		// Creates the buffer for the depth.
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		VT_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer Is Incomplete!");

		// Unbinds Framebuffer After Completion.
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/**
	 * @brief Binds the framebuffer object. 
	 */
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	/**
	 * @brief Unbinds the framebuffer object. 
	 */
	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/**
	 * @brief Resizes the frame buffer.
	 * @param p_Width The new width.
	 * @param p_Height The new height.
	 */
	void OpenGLFramebuffer::Resize(uint32_t p_Width, uint32_t p_Height)
	{
		m_Specification.Width = p_Width;
		m_Specification.Height = p_Height;

		Invalidate();
	}
}