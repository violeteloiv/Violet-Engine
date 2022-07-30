/////////////////
///
/// OpenGLShader.h
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 30th, 2022
///
/// A shader is a program which allows
/// you to communicate with the GPU directly
/// using GLSL. GLSL is the shader language
/// Violet uses. 
/// 
/// This is an OpenGL implementation of a
/// Shader.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORM_OPEN_GL_SHADER_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_OPEN_GL_SHADER_H_INCLUDED__

#include <glm/glm.hpp>

#include "Violet/Renderer/Shader.h"

// remove <3
typedef unsigned int GLenum;

namespace Violet
{
	/**
	 * @brief OpenGL Implementation of a Shader.
	 */
	class OpenGLShader : public Shader
	{
	public: // Constructors & Deconstructors
		OpenGLShader(const std::string& p_Filepath);
		OpenGLShader(const std::string& p_Name, const std::string& p_VertexSource, const std::string& p_FragmentSource);
		virtual ~OpenGLShader();
	public: // Main Functionality
		virtual void Bind() const override;
		virtual void Unbind() const override;
	public: // Uniforms
		virtual void SetInt(const std::string& p_Name, int p_Value) override;
		virtual void SetIntArray(const std::string& p_Name, int* p_Values, uint32_t p_Count) override;
		virtual void SetFloat(const std::string& p_Name, float p_Value) override;
		virtual void SetFloat2(const std::string& p_Name, const glm::vec2& p_Value) override;
		virtual void SetFloat3(const std::string& p_Name, const glm::vec3& p_Value) override;
		virtual void SetFloat4(const std::string& p_Name, const glm::vec4& p_Value) override;
		virtual void SetMat4(const std::string& p_Name, const glm::mat4& p_Value) override;
	public: // Getters
		/**
		 * @brief Gets the name of the shader.
		 * @returns The name of the shader.
		 */
		virtual const std::string& GetName() const override { return m_Name; }
	public: // Uniform Internals
		void UploadUniformInt(const std::string& p_Name, int p_Value);
		void UploadUniformIntArray(const std::string& p_Name, int* p_Values, uint32_t p_Count);
		void UploadUniformFloat(const std::string& p_Name, float p_Value);
		void UploadUniformFloat2(const std::string& p_Name, const glm::vec2& p_Value);
		void UploadUniformFloat3(const std::string& p_Name, const glm::vec3& p_Value);
		void UploadUniformFloat4(const std::string& p_Name, const glm::vec4& p_Value);
		void UploadUniformMat3(const std::string& p_Name, const glm::mat3& p_Matrix);
		void UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix);
	private: // Helpers
		std::string ReadFile(const std::string& p_Filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& p_Source);
		void Compile(const std::unordered_map<GLenum, std::string>& p_ShaderSources);
	private: // Private Member Variables
		uint32_t m_RendererID;
		std::string m_Name;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_OPEN_GL_SHADER_H_INCLUDED__
