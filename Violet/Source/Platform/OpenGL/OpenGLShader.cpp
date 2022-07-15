/////////////////
///
/// OpenGLShader.cpp
/// Violet McAllister
/// July 13th, 2022
/// Updated: July 15th, 2022
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

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Violet
{
	/**
	 * @brief Converts a shader type in string form to a shader
	 * type in GLenum form.
	 * @param p_Type The string type being converted.
	 * @returns The Glenum converted type.
	 */
	static GLenum ShaderTypeFromString(const std::string& p_Type)
	{
		if (p_Type == "vertex")
			return GL_VERTEX_SHADER;
		if (p_Type == "fragment" || p_Type == "pixel")
			return GL_FRAGMENT_SHADER;

		VT_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	/**
	 * @brief Constructs an OpenGLShader object using the file path.
	 * @param p_Filepath The filepath to the shader code.
	 */
	OpenGLShader::OpenGLShader(const std::string& p_Filepath)
	{
		std::string source = ReadFile(p_Filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		// Extract Name From Filepath
		auto lastSlash = p_Filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = p_Filepath.rfind('.');
		auto count = lastDot == std::string::npos ? p_Filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = p_Filepath.substr(lastSlash, count);
	}
	
	/**
	 * @brief Constructs and OpenGLShader object from source.
	 * @param p_VertexSource The vertex shader source.
	 * @param p_FragmentSource The fragment shader source.
	 */ 
	OpenGLShader::OpenGLShader(const std::string& p_Name, const std::string& p_VertexSource, const std::string& p_FragmentSource)
		: m_Name(p_Name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = p_VertexSource;
		sources[GL_FRAGMENT_SHADER] = p_FragmentSource;
		Compile(sources);
	}

	/**
	 * @brief Deconstructs an OpenGL Shader object. 
	 */
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	/**
	 * @brief Reads file data.
	 * @param p_Filepath The file path.
	 * @returns The file as a string.
	 */
	std::string OpenGLShader::ReadFile(const std::string& p_Filepath)
	{
		std::string result;
		std::ifstream in(p_Filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			// Reads File Data into result
			in.seekg(0, std::ios::end);
			
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				VT_CORE_ERROR("Could not read from file '{0}'", p_Filepath);
			}
		}
		else
		{
			VT_CORE_ERROR("Could Not Open File '{0}'", p_Filepath);
		}

		return result;
	}

	/**
	 * @brief Takes a shader source and breaks it down into vertex and
	 * fragment shader strings.
	 * @param p_Source The file source.
	 * @returns A map between a GLenum and it's corresponding string.
	 */
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& p_Source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = p_Source.find(typeToken, 0); // Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = p_Source.find_first_of("\r\n", pos);
			VT_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type " keyword)
			std::string type = p_Source.substr(begin, eol - begin);
			VT_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = p_Source.find_first_not_of("\r\n", eol); // Start of shader code after shader type declaration line
			VT_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = p_Source.find(typeToken, nextLinePos); // Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? p_Source.substr(nextLinePos) : p_Source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	/**
	 * @brief Compiles a shader program from shader sources.
	 * @param p_ShaderSources the map of shader sources.
	 */
	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& p_ShaderSources)
	{
		GLuint program = glCreateProgram();
		VT_CORE_ASSERT(p_ShaderSources.size() <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : p_ShaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				VT_CORE_ERROR("{0}", infoLog.data());
				VT_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			VT_CORE_ERROR("{0}", infoLog.data());
			VT_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
	}

	/**
	 * @brief Binds an OpenGL Shader.
	 */
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	/**
	 * @brief Unbinds an OpenGL Shader.
	 */
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	/**
	 * @brief Uploads an integer value to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The integer value.
	 */
	void OpenGLShader::SetInt(const std::string& p_Name, int p_Value)
	{
		UploadUniformInt(p_Name, p_Value);
	}

	/**
	 * @brief Uploads a set of three float values to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The three float values as a vector.
	 */
	void OpenGLShader::SetFloat3(const std::string& p_Name, const glm::vec3& p_Value)
	{
		UploadUniformFloat3(p_Name, p_Value);
	}

	/**
	 * @brief Uploads a set of four float values to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The four float values as a vector.
	 */
	void OpenGLShader::SetFloat4(const std::string& p_Name, const glm::vec4& p_Value)
	{
		UploadUniformFloat4(p_Name, p_Value);
	}

	/**
	 * @brief Uploads a 4x4 matrix to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The 4x4 matrix.
	 */
	void OpenGLShader::SetMat4(const std::string& p_Name, const glm::mat4& p_Value)
	{
		UploadUniformMat4(p_Name, p_Value);
	}

	/**
	 * @brief Uploads an integer value to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The integer value.
	 */
	void OpenGLShader::UploadUniformInt(const std::string& p_Name, int p_Value)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform1i(location, p_Value);
	}

	/**
	 * @brief Uploads a float value to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The float value.
	 */
	void OpenGLShader::UploadUniformFloat(const std::string& p_Name, float p_Value)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform1f(location, p_Value);
	}

	/**
	 * @brief Uploads a set of two float values to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The two float values as a vector.
	 */
	void OpenGLShader::UploadUniformFloat2(const std::string& p_Name, const glm::vec2& p_Value)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform2f(location, p_Value.x, p_Value.y);
	}

	/**
	 * @brief Uploads a set of three float values to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The three float values as a vector.
	 */
	void OpenGLShader::UploadUniformFloat3(const std::string& p_Name, const glm::vec3& p_Value)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform3f(location, p_Value.x, p_Value.y, p_Value.z);
	}

	/**
	 * @brief Uploads a set of four float values to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The four float values as a vector.
	 */
	void OpenGLShader::UploadUniformFloat4(const std::string& p_Name, const glm::vec4& p_Value)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniform4f(location, p_Value.x, p_Value.y, p_Value.z, p_Value.w);
	}

	/**
	 * @brief Uploads a 3x3 matrix to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The 3x3 matrix.
	 */
	void OpenGLShader::UploadUniformMat3(const std::string& p_Name, const glm::mat3& p_Matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}

	/**
	 * @brief Uploads a 4x4 matrix to the GPU for use in a shader.
	 * @param p_Name The name of the uniform in the shader.
	 * @param p_Value The 4x4 matrix.
	 */
	void OpenGLShader::UploadUniformMat4(const std::string& p_Name, const glm::mat4& p_Matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, p_Name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(p_Matrix));
	}
}
