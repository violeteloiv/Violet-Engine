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
	public: // Creator
		static Shader* Create(const std::string& p_VertexSource, const std::string& p_FragmentSource);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_SHADER_H_INCLUDED__