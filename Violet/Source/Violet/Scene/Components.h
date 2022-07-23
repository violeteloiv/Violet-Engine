/////////////////
///
/// Components.h
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 22nd, 2022
///
/// Contains definitions and implementations
/// for all of the Violet API's components.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__

#include <glm/glm.hpp>

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
	 * A Sprite Renderer (color) component
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
}

#endif // __VIOLET_ENGINE_SCENE_COMPONENTS_H_INCLUDED__