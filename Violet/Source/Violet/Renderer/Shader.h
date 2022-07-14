/////////////////
///
/// Shader.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 13th, 2022
///
/// A shader is a program which allows
/// you to communicate with the GPU directly
/// using GLSL. GLSL is the shader language
/// Violet uses.
/// 
/// This also contains the functionality of
/// a Shader Library, allowing for storage
/// of shaders within the API instead of on
/// the client's end.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__

#include <string>

namespace Violet
{
	/**
	 * @brief Abstract Shader class used to
	 * define implementations of a Shader
	 * using a graphics API.
	 */
	class Shader
	{
	public: // Deconstructors
		virtual ~Shader() = default;
	public: // Main Functionality
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public: // Getters
		virtual const std::string& GetName() const = 0;
	public: // Creator
		static Ref<Shader> Create(const std::string& p_Filepath);
		static Ref<Shader> Create(const std::string& p_Name, const std::string& p_VertexSource, const std::string& p_FragmentSource);
	};

	class ShaderLibrary
	{
	public: // Main Functionality
		void Add(const std::string& p_Name, const Ref<Shader>& p_Shader);
		void Add(const Ref<Shader>& p_Shader);
		Ref<Shader> Load(const std::string& p_Filepath);
		Ref<Shader> Load(const std::string& p_Name, const std::string& p_Filepath);
		Ref<Shader> Get(const std::string& p_Name);
		bool Exists(const std::string& p_Name);
	private: // Private Member Variables
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__