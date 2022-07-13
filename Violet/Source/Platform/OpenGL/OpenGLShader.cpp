/////////////////
///
/// OpenGLShader.cpp
/// Violet McAllister
/// July 13th, 2022
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

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Violet
{
	/**
	 * @brief Constructs and OpenGLShader object from source.
	 * @param p_VertexSource The vertex shader source.
	 * @param p_FragmentSource The fragment shader source.
	 */ 
	OpenGLShader::OpenGLShader(const std::string& p_VertexSource, const std::string& p_FragmentSource)
	{
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = p_VertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			VT_CORE_ERROR("{0}", infoLog.data());
			VT_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = p_FragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			VT_CORE_ERROR("{0}", infoLog.data());
			VT_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

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
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			VT_CORE_ERROR("{0}", infoLog.data());
			VT_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	/**
	 * @brief Deconstructs an OpenGL Shader object. 
	 */
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
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
