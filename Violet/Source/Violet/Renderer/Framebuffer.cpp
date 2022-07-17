/////////////////
///
/// Framebuffer.cpp
/// Violet McAllister
/// July 17th, 2022
///
/// A framebuffer contains information
/// about the currently rendered pixels 
/// on the screen to be used for later.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Framebuffer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	/**
	 * @brief Creates a Framebuffer object given an API.
	 * @brief p_Specification The specification for the Framebuffer.
	 */
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& p_Specification)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(p_Specification);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}