/////////////////
///
/// OpenGLContext.h
/// Violet McAllister
/// July 11th, 2022
///
/// An OpenGL implementation of a graphics context.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORN_OPEN_GL_CONTEXT_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORN_OPEN_GL_CONTEXT_H_INCLUDED__

#include "Violet/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Violet
{
	/**
	 * @brief OpenGL Implementation of a graphics context.
	 */
	class OpenGLContext : public GraphicsContext
	{
	public: // Constructors & Deconstructors
		OpenGLContext(GLFWwindow* p_WindowHandle);
	public: // Main Functionality
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private: // Private Member Variables
		GLFWwindow* m_WindowHandle;
	};
}

#endif // __VIOLET_ENGINE_PLATFORN_OPEN_GL_CONTEXT_H_INCLUDED__