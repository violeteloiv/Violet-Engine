/////////////////
///
/// Shader.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 12th, 2022
///
/// A shader is a program which allows
/// you to communicate with the GPU directly
/// using GLSL. GLSL is the shader language
/// Violet uses. 
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__

#include <string>

#include <glm/glm.hpp>

namespace Violet
{
	class Shader
	{
	public: // Constructors & Deconstructors
		Shader(const std::string& p_VertexSource, const std::string& p_FragmentSource);
		~Shader();
	public: // Main Functionality
		void Bind() const;
		void Unbind() const;
	public: // Uniforms
		void UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix);
	private: // Private Member Variables
		uint32_t m_RendererID;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__