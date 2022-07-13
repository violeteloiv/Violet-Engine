/////////////////
///
/// Shader.cpp
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 13th, 2022
///
/// A shader is a program which allows
/// you to communicate with the GPU directly
/// using GLSL. GLSL is the shader language
/// Violet uses. 
///
/////////////////

#include "vtpch.h"

#include "Violet/Renderer/Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "Violet/Renderer/Renderer.h"

namespace Violet
{
	/**
	 * @brief Creates a Shader object based on the current API.
	 * @param p_VertexSource The vertex source for the shader.
	 * @param p_FragmentSource The fragment source for the shader.
	 */
	Ref<Shader> Shader::Create(const std::string& p_VertexSource, const std::string& p_FragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(p_VertexSource, p_FragmentSource);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}