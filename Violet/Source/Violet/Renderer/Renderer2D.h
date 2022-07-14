/////////////////
///
/// Renderer2D.h
/// Violet McAllister
/// July 14th, 2022
///
/// Violet's main 2D Renderer which
/// handles drawing 2D shapes.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__

#include "Violet/Renderer/OrthographicCamera.h"

namespace Violet
{
	/**
	 * @brief Handles beginning and ending
	 * scenes as well as drawing 2D shapes.
	 */
	class Renderer2D
	{
	public: // Initializer & Shutdown
		static void Init();
		static void Shutdown();
	public: // Scene
		static void BeginScene(const OrthographicCamera& p_Camera);
		static void EndScene();
	public: // Main Functionality
		static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
		static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
	};
}

#endif // __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__