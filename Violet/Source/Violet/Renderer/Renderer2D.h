/////////////////
///
/// Renderer2D.h
/// Violet McAllister
/// July 14th, 2022
/// Updated: July 30th, 2022
///
/// Violet's main 2D Renderer which
/// handles drawing 2D shapes.
///
/////////////////

#ifndef __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__
#define __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__

#include "Violet/Renderer/Camera.h"
#include "Violet/Renderer/EditorCamera.h"
#include "Violet/Renderer/OrthographicCamera.h"
#include "Violet/Renderer/Texture.h"
#include "Violet/Scene/Components.h"

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
		static void BeginScene(const Camera& p_Camera, const glm::mat4& p_Transform);
		static void BeginScene(const EditorCamera& p_Camera);
		static void BeginScene(const OrthographicCamera& p_Camera); // TODO: Remove
		static void EndScene();
	public: // Batching
		static void Flush();
	public: // Main Functionality
		static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
		static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const glm::vec4& p_Color);
		static void DrawQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& p_Transform, const glm::vec4& p_Color, int p_EntityID = -1);
		static void DrawQuad(const glm::mat4& p_Transform, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f), int p_EntityID = -1);
		static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
		static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const glm::vec4& p_Color);
		static void DrawRotatedQuad(const glm::vec2& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& p_Position, const glm::vec2& p_Size, float p_Rotation, const Ref<Texture2D>& p_Texture, float p_TilingFactor = 1.0f, const glm::vec4& p_TintColor = glm::vec4(1.0f));
		static void DrawSprite(const glm::mat4& p_Transform, SpriteRendererComponent& p_SRC, int p_EntityID);
	public: // Statistics
		/**
		 * @brief Contains Renderer stats. 
		 */
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			/**
			 * @brief Gets the total number of vertices drawn.
			 * @returns The total number of vertices drawn.
			 */
			uint32_t GetTotalVertexCount() const { return QuadCount * 4; }

			/**
			 * @brief Gets the total number of indices drawn.
			 * @returns The total number of indices drawn.
			 */
			uint32_t GetTotalIndexCount() const { return QuadCount * 6; }
		};
	public: // Statistics Functions
		static void ResetStats();
		static Statistics GetStats();
	private: // Helpers
		static void StartBatch();
		static void NextBatch();
	};
}

#endif // __VIOLET_ENGINE_RENDERER_2D_H_INCLUDED__
