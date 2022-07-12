/////////////////
///
/// Shader.h
/// Violet McAllister
/// July 11th, 2022
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
	private: // Private Member Variables
		uint32_t m_RendererID;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__