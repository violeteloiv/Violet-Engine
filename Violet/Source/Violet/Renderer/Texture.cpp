/////////////////
///
/// Texture.cpp
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 15th, 2022
///
/// A texture is a collection of
/// data which can be uploaded to
/// the GPU and processed as an
/// image.
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	/**
	 * @brief Creates a Texture2D object based on the current API using
	 * only the width and height.
	 * @param p_Width The width of the texture to create.
	 * @param p_Height The height of the texture to create.
	 */
	Ref<Texture2D> Texture2D::Create(uint32_t p_Width, uint32_t p_Height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(p_Width, p_Height);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	/**
	 * @brief Creates a Texture2D object based on the current API.
	 * @param p_Filepath The path to the image file.
	 */
	Ref<Texture2D> Texture2D::Create(const std::string& p_Filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(p_Filepath);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}