/////////////////
///
/// OpenGLFramebuffer.cpp
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 30th, 2022
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
	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils
	{
		/**
		 * @brief Determines the texture target enum.
		 * @param p_Multisampled If the texture is multisampled.
		 * @returns The determined texture target enum.
		 */
		static GLenum TextureTarget(bool p_Multisampled)
		{
			return p_Multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		/**
		 * @brief Creates textures given an amount and if it's multisampled.
		 * @param p_Multisampled If the texture should be multisampled.
		 * @param p_OutID The ID of the textures generated.
		 * @param p_Count The number of textures to generate.
		 */
		static void CreateTextures(bool p_Multisampled, uint32_t* p_OutID, uint32_t p_Count)
		{
			glCreateTextures(TextureTarget(p_Multisampled), p_Count, p_OutID);
		}

		/**
		 * @brief Binds a texture.
		 * @param p_Multisampled If the texture should be multisampled.
		 * @param p_ID The id of the texture to bind.
		 */
		static void BindTexture(bool p_Multisampled, uint32_t p_ID)
		{
			glBindTexture(TextureTarget(p_Multisampled), p_ID);
		}

		/**
		 * @brief Attaches a color texture to a texture.
		 * @param p_ID The id of the image.
		 * @param p_Samples The number of samples.
		 * @param p_Format The format.
		 * @param p_Width The data width.
		 * @param p_Height The data height.
		 * @param p_Index The attachment index.
		 */
		static void AttachColorTexture(uint32_t p_ID, int p_Samples, GLenum p_Format, uint32_t p_Width, uint32_t p_Height, int p_Index)
		{
			bool multisampled = p_Samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, p_Samples, p_Format, p_Width, p_Height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, p_Format, p_Width, p_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + p_Index, TextureTarget(multisampled), p_ID, 0);
		}

		/**
		 * @brief Attaches a depth texture to a texture.
		 * @param p_ID The id of the texture.
		 * @param p_Samples The number of samples.
		 * @param p_Format The format of the texture.
		 * @param p_AttachmentType The type of attachment.
		 * @param p_Width The data width.
		 * @param p_Height The data height.
		 */
		static void AttachDepthTexture(uint32_t p_ID, int p_Samples, GLenum p_Format, GLenum p_AttachmentType, uint32_t p_Width, uint32_t p_Height)
		{
			bool multisampled = p_Samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, p_Samples, p_Format, p_Width, p_Height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, p_Format, p_Width, p_Height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, p_AttachmentType, TextureTarget(multisampled), p_ID, 0);
		}

		/**
		 * @brief Checks if a format is supported by violet.
		 * @param p_Format The format to check.
		 * @returns If the format is supported.
		 */
		static bool IsDepthFormat(FramebufferTextureFormat p_Format)
		{
			switch (p_Format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8: return true;
			}

			return false;
		}
	}

	/**
	 * @brief Constructs an OpenGL Framebuffer object with reference
	 * to a specification.
	 */
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& p_Specification)
		: m_Specification(p_Specification)
	{
		for (auto spec : m_Specification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				m_ColorAttachmentSpecifications.emplace_back(spec);
			else
				m_DepthAttachmentSpecification = spec;
		}

		Invalidate();
	}

	/**
	 * @brief Deconstructs an OpenGL Framebuffer object. 
	 */
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
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
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		// Creates a Framebuffer object.
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = m_Specification.Samples > 1;

		// Attachments
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, m_Specification.Width, m_Specification.Height, i);
					break;
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &m_DepthAttachment, 1);
			Utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
				break;
			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			VT_CORE_ASSERT(m_ColorAttachments.size() <= 4);
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

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
		if (p_Width == 0 || p_Height == 0 || p_Width > s_MaxFramebufferSize || p_Height > s_MaxFramebufferSize)
		{
			VT_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", p_Width, p_Height);
			return;
		}

		m_Specification.Width = p_Width;
		m_Specification.Height = p_Height;

		Invalidate();
	}
}
