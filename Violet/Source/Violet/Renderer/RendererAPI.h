/////////////////
///
/// RendererAPI.h
/// Violet McAllister
/// July 12th, 2022
/// Updated: July 13th, 2022
///
/// Defines what graphics APIs are available
/// to use and allows for better abstraction.
/// 
/// Defines functions that are required from
/// all render APIs.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_API_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_API_H_INCLUDED__

#include <glm/glm.hpp>

#include "Violet/Renderer/VertexArray.h"

namespace Violet
{
	/**
	 * @brief Defins available graphics APIs and
	 * basic graphics functionality.
	 */
	class RendererAPI
	{
	public: // API
		enum class API
		{
			None = 0, OpenGL = 1
		};
	public: // Initializer
		virtual void Init() = 0;
	public: // Main Functionality
		virtual void SetClearColor(const glm::vec4& p_Color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& p_VertexArray) = 0;
	public: // Getter
		/**
		 * @brief Gets the static API.
		 * @returns The static API.
		 */
		inline static API GetAPI() { return s_API; }
	private: // Private Static Member Variables
		static API s_API;
	};
}

#endif // __VIOLET_ENGINE_RENDERER_API_H_INCLUDED__