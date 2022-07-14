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
	 * @param p_Filepath The file path to a shader program.
	 */
	Ref<Shader> Shader::Create(const std::string& p_Filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(p_Filepath);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	/**
	 * @brief Creates a Shader object based on the current API.
	 * @param p_VertexSource The vertex source for the shader.
	 * @param p_FragmentSource The fragment source for the shader.
	 */
	Ref<Shader> Shader::Create(const std::string& p_Name, const std::string& p_VertexSource, const std::string& p_FragmentSource)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    VT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(p_Name, p_VertexSource, p_FragmentSource);
		}

		VT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	/**
	 * @brief Adds a shader to the ShaderLibrary given its name and the shader itself.
	 * @param p_Name The name of the shader.
	 * @param p_Shader The shader itself.
	 */
	void ShaderLibrary::Add(const std::string& p_Name, const Ref<Shader>& p_Shader)
	{
		VT_CORE_ASSERT(!Exists(p_Name), "Shader Already Exists!");
		m_Shaders[p_Name] = p_Shader;
	}

	/**
	 * @brief Adds a shader to the ShaderLibrary given the shader itself.
	 * @param p_Shader The shader itself.
	 */
	void ShaderLibrary::Add(const Ref<Shader>& p_Shader)
	{
		auto& name = p_Shader->GetName();
		Add(name, p_Shader);
	}

	/**
	 * @brief Loads a shader into the ShaderLibrary from the file itself.
	 * @param p_Filepath The path to the file.
	 * @returns The shader that was loaded.
	 */
	Ref<Shader> ShaderLibrary::Load(const std::string& p_Filepath)
	{
		auto shader = Shader::Create(p_Filepath);
		Add(shader);
		return shader;
	}

	/**
	 * @brief Loads a shader into the ShaderLibrary with a name and the file itself. 
	 * @param p_Name The name to give to the Shader.
	 * @param p_Filepath The path to the file.
	 * @returns The loaded shader.
	 */
	Ref<Shader> ShaderLibrary::Load(const std::string& p_Name, const std::string& p_Filepath)
	{
		auto shader = Shader::Create(p_Filepath);
		Add(p_Name, shader);
		return shader;
	}
	
	/**
	 * @brief Gets a shader from the ShaderLibrary based on name.
	 * @param p_Name The name of the shader.
	 * @returns The shader with that name.
	 */
	Ref<Shader> ShaderLibrary::Get(const std::string& p_Name)
	{
		VT_CORE_ASSERT(Exists(p_Name), "Shader Not Found!");
		return m_Shaders[p_Name];
	}

	/**
	 * @brief Finds if a shader with a name exists.
	 * @param p_Name The name of the shader to be checked.
	 * @returns If the shader with that name exists.
	 */
	bool ShaderLibrary::Exists(const std::string& p_Name)
	{
		return m_Shaders.find(p_Name) != m_Shaders.end();
	}

}