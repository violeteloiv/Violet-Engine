/////////////////
///
/// GraphicsContext.h
/// Violet McAllister
/// July 11th, 2022
///
/// A graphics context is what the renderer
/// actually displays to. It contains buffers which
/// pixels are drawn to and then displayed.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_GRAPHICS_CONTEXT_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_GRAPHICS_CONTEXT_H_INCLUDED__

namespace Violet
{
	/**
	 * @brief Class definition of a Graphics Context. 
	 */
	class GraphicsContext
	{
	public: // Main Functionality
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_GRAPHICS_CONTEXT_H_INCLUDED__