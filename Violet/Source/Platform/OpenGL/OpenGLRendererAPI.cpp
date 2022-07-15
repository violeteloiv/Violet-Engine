/////////////////
///
/// OpenGLRendererAPI.cpp
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 15th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
/// 
/// Implements functions required for all
/// graphics APIs for OpenGL.
///
/////////////////

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Violet
{
	/**
	 * @brief Initializes OpenGL functions. 
	 */
	void OpenGLRendererAPI::Init()
	{
		VT_PROFILE_FUNCTION();

		// Enable Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Enable Depth Testing
		glEnable(GL_DEPTH_TEST);
	}

	/**
	 * @brief Updates the GL Viewport
	 * @param p_X The x position of the view port.
	 * @param p_Y The y position of the view port.
	 * @param p_Width The width of the view port.
	 * @param p_Height The height of the view port.
	 */
	void OpenGLRendererAPI::SetViewport(uint32_t p_X, uint32_t p_Y, uint32_t p_Width, uint32_t p_Height)
	{
		glViewport(p_X, p_Y, p_Width, p_Height);
	}

	/**
	 * @brief Wrapper for glClearColor().
	 * @param p_Color The clear color to be submitted to
	 * OpenGL.
	 */
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& p_Color)
	{
		glClearColor(p_Color.r, p_Color.g, p_Color.b, p_Color.a);
	}

	/**
	 * @brief Wrapper for glClear(). Clears the color buffer
	 * bit and depth buffer bit.
	 */
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	 * @brief Wrapper for glDrawElements(). Draws an object
	 * given a vertex array with vertex and index data.
	 * @param p_VertexArray The supplied Vertex Array for
	 * submission.
	 */
	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& p_VertexArray)
	{
		glDrawElements(GL_TRIANGLES, p_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}