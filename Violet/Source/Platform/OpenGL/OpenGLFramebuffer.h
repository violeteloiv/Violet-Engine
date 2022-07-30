/////////////////
///
/// OpenGLFramebuffer.h
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
		virtual int ReadPixel(uint32_t p_AttachmentIndex, int p_X, int p_Y) override;
		virtual void ClearAttachment(uint32_t p_AttachmentIndex, int p_Value) override;
	public: // Getters
		/**
		 * @brief Gets the color attachment for the framebuffer.
		 * @param p_Index The color attachment index (optional).
		 * @returns The color attachment for the framebuffer.
		 */
		virtual uint32_t GetColorAttachmentRendererID(uint32_t p_Index = 0) const override { VT_CORE_ASSERT(p_Index < m_ColorAttachments.size()); return m_ColorAttachments[p_Index]; }

		/**
		 * @brief Gets the current specification.
		 * @returns The currnent specification.
		 */
		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private: // Private Member Functions
		uint32_t m_RendererID = 0;
		FramebufferSpecification m_Specification;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_FRAMEBUFFER_H_INCLUDED__
