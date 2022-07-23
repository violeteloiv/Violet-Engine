/////////////////
///
/// Components.h
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 23nd, 2022
///
/// Contains definitions and implementations
/// for all of the Violet API's components.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__

#include <glm/glm.hpp>

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
		glm::mat4 Transform{ 1.0f };
	public: // Constructors
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;

		/**
		 * @brief Constructs a transform using a different transform.
		 * @param p_Transform The transform to be added.
		 */
		TransformComponent(const glm::mat4& p_Transform)
			: Transform(p_Transform) {}
	public: // Operators
		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& const () { return Transform; }
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
		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;
		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*)> OnDestroyFunction;
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;
	public: // Main Functionality
		/**
		 * @brief Binds an object to the native script component. 
		 */
		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };
			DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { ((T*)instance)->OnUpdate(ts); };
		}
	};
}

#endif // __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__