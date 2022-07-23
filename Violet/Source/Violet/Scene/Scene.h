/////////////////
///
/// Scene.h
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 23rd, 2022
///
/// A Scene contains information about all of the
/// entities and how to render and deal with them.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_H_INCLUDED__

#include <entt.hpp>

#include "Violet/Core/Timestep.h"

namespace Violet
{
	class Entity;

	/**
	 * @brief The scene handles all of the entities in
	 * the application.
	 */
	class Scene
	{
	public: // Constructors & Deconstuctors
		Scene();
		~Scene();
	public: // Main Functionality
		Entity CreateEntity(const std::string& p_Name = std::string());
	public: // Viole Internals
		void OnUpdate(Timestep p_Timestep);
		void OnViewportSize(uint32_t p_Width, uint32_t p_Height);
	private: // Private Member Variables
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	private: // Friend Classes
		friend class Entity;
		friend class SceneHierarchyPanel;
	};
}

#endif // __VIOLET_ENGINE_SCENE_H_INCLUDED__
