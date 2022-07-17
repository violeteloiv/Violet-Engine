/////////////////
///
/// OpenGLFramebuffer.h
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

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_FRAMEBUFFER_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_FRAMEBUFFER_H_INCLUDED__

#include "Violet/Renderer/Framebuffer.h"

namespace Violet
{
	/**
	 * @brief An OpenGL implementation of a Framebuffer. 
	 */
	class OpenGLFramebuffer : public Framebuffer
	{
	public: // Constuctors & Deconstructors
		OpenGLFramebuffer(const FramebufferSpecification& p_Specification);
		virtual ~OpenGLFramebuffer();
	public: // Main Functionality
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t p_Width, uint32_t p_Height) override;
	public: // Getters
		/**
		 * @brief Gets the color attachment for the framebuffer.
		 * @returns The color attachment for the framebuffer.
		 */
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		/**
		 * @brief Gets the current specification.
		 * @returns The currnent specification.
		 */
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private: // Private Member Functions
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_FRAMEBUFFER_H_INCLUDED__