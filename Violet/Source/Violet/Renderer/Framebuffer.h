/////////////////
///
/// Framebuffer.h
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 30th, 2022
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
	 * @brief Available texture formats violet supports.
	 */
	enum class FramebufferTextureFormat
	{
		None = 0,

		// Color
		RGBA8,

		// Depth/Stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	/**
	 * @brief Specification for the texture format
	 * of the framebuffer.
	 */
	struct FramebufferTextureSpecification
	{
	public: // Constructors
		FramebufferTextureSpecification() = default;

		/**
		 * @brief Constructs a Framebuffer Texture Specification given a
		 * specific format.
		 */
		FramebufferTextureSpecification(FramebufferTextureFormat p_Format)
			: TextureFormat(p_Format) { }
	public: // Public Member Variables
		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: Filtering & Wrapping
	};

	/**
	 * @brief Specification for the attachments on the
	 * current Framebuffer.
	 */
	struct FramebufferAttachmentSpecification
	{
	public:
		FramebufferAttachmentSpecification() = default;

		/**
		 * @brief Consstructs a Framebuffer Attachment Specification given a list of attachments.
		 * @param p_Attachments The attachments for the framebuffer.
		 */
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> p_Attachments)
			: Attachments(p_Attachments) { }
	public: // Public Member Variables
		std::vector<FramebufferTextureSpecification> Attachments;
	};

	/**
	 * @brief Specification or settings for the
	 * framebuffer.
	 */
	struct FramebufferSpecification
	{
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
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
		virtual uint32_t GetColorAttachmentRendererID(uint32_t p_Index = 0) const = 0;
		virtual const FramebufferSpecification& GetSpecification() const = 0;
	public: // Creator
		static Ref<Framebuffer> Create(const FramebufferSpecification& p_Specification);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_FRAMEBUFFER_H_INCLUDED__
