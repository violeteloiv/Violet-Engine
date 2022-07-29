/////////////////
///
/// Components.h
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 28th, 2022
///
/// Contains definitions and implementations
/// for all of the Violet API's components.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Violet/Scene/SceneCamera.h"
#include "Violet/Scene/ScriptableEntity.h"

namespace Violet
{
	/**
	 * @brief A Tag (name) component for the entity
	 * component system.
	 */
	struct TagComponent
	{
	public: // Variables
		std::string Tag;
	public: // Constructors
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;

		/**
		 * @brief Constructs a tag component using the name.
		 * @param p_Tag The name of the entity.
		 */
		TagComponent(const std::string& p_Tag)
			: Tag(p_Tag) {}
	};

	/**
	 * @brief A Transform (position, size, rotation) component
	 * for the entity component system.
	 */
	struct TransformComponent
	{
	public: // Variables
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
	public: // Constructors
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		/**
		 * @brief Constructs a transform using its position.
		 * @param p_Translation The translation of the entity.
		 */
		TransformComponent(const glm::vec3& p_Translation)
			: Translation(p_Translation) {}
	public: // Operators
		/**
		 * @brief Gets the transform of the entity given its
		 * translation, rotation, and scale.
		 */
		glm::mat4 GetTransform()
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	/**
	 * @brief A Sprite Renderer (color) component
	 * for the entity component system.
	 */
	struct SpriteRendererComponent
	{
	public: // Variables
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
	public: // Constructors
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;

		/**
		 * @brief Constructs a sprite renderer component.
		 * @param p_Color The color to be added.
		 */
		SpriteRendererComponent(const glm::vec4& p_Color)
			: Color(p_Color) {}
	};

	/**
	 * @brief A Camera component for the
	 * entity component system.
	 */
	struct CameraComponent
	{
	public: // Variables
		SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;
	public: // Constructors
		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	/**
	 * @brief A native script component for the
	 * entity component system.
	 */
	struct NativeScriptComponent
	{
	public: // Variables
		ScriptableEntity* Instance = nullptr;
	public: // Functions
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);
	public: // Main Functionality
		/**
		 * @brief Binds an object to the native script component. 
		 */
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}

#endif // __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__
