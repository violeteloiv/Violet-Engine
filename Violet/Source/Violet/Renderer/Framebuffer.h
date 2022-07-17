/////////////////
///
/// Framebuffer.h
/// Violet McAllister
/// July 17th, 2022
///
/// A framebuffer contains information
/// about the currently rendered pixels 
/// on the screen to be used for later.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_FRAMEBUFFER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_FRAMEBUFFER_H_INCLUDED__

#include "Violet/Core/Base.h"

namespace Violet
{
	/**
	 * @brief Specification or settings for the
	 * framebuffer.
	 */
	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		// Framebuffer format
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	/**
	 * @brief The framebuffer contains information about
	 * the pixels on the screen.
	 */
	class Framebuffer
	{
	public: // Deconstructor
		virtual ~Framebuffer() = default;
	public: // Main Functionality
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(uint32_t p_Width, uint32_t p_Height) = 0;
	public: // Getters
		virtual uint32_t GetColorAttachmentRendererID() const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
	public: // Creator
		static Ref<Framebuffer> Create(const FramebufferSpecification& p_Specification);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_FRAMEBUFFER_H_INCLUDED__