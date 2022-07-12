/////////////////
///
/// OpenGLContext.cpp
/// Violet McAllister
/// July 11th, 2022
///
/// An OpenGL implementation of a graphics context.
///
/////////////////

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Violet
{
	/**
	 * @brief Constructs an OpenGLContext using a window pointer.
	 * @param p_WindowHandle The window handle for the context.
	 */
	OpenGLContext::OpenGLContext(GLFWwindow* p_WindowHandle)
		: m_WindowHandle(p_WindowHandle)
	{
		VT_CORE_ASSERT(p_WindowHandle, "Window Handle Is Null!");
	}

	/**
	 * @brief Initizlies an OpenGL Context. 
	 */
	void OpenGLContext::Init()
	{
		// Makes the window the current window.
		glfwMakeContextCurrent(m_WindowHandle);
		// Gets OpenGL functionality from drivers.
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VT_CORE_ASSERT(status, "[GLAD ERROR] Failed To Initialize Glad!");

		VT_CORE_INFO("OpenGL Info:");
		VT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		VT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		VT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	/**
	`* @brief GLFW swaps the framebuffers from front to back allowing rendering to
	 * be smooth. Pixels are rendered to a back buffer before displayed on
	 * the screen. This switches the buffer. 
	 */
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}