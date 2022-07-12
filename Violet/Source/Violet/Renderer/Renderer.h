/////////////////
///
/// Renderer.h
/// Violet McAllister
/// July 11th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_H_INCLUDED__

namespace Violet
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	/**
	 * @brief Contains information about the current Renderer API.
	 */
	class Renderer
	{
	public: // Getter
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private: // Private Static Member Variables
		static RendererAPI s_RendererAPI;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_H_INCLUDED__