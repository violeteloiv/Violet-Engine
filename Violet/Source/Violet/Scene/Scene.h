/////////////////
///
/// Scene.h
/// Violet McAllister
/// July 22nd, 2022
/// Updated: July 30th, 2022
///
/// A Scene contains information about all of the
/// entities and how to render and deal with them.
///
/////////////////

#ifndef __VIOLET_ENGINE_SCENE_H_INCLUDED__
#define __VIOLET_ENGINE_SCENE_H_INCLUDED__

#include <entt.hpp>

#include "Violet/Core/Timestep.h"
#include "Violet/Renderer/EditorCamera.h"

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
		void DestroyEntity(Entity p_Entity);
	public: // Viole Internals
		void OnUpdateRuntime(Timestep p_Timestep);
		void OnUpdateEditor(Timestep p_Timestep, EditorCamera& p_Camera);
		void OnViewportSize(uint32_t p_Width, uint32_t p_Height);
	public: // Getters
		Entity GetPrimaryCameraEntity();
	private: // Component
		template<typename T>
		void OnComponentAdded(Entity p_Entity, T& p_Component);
	private: // Private Member Variables
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	private: // Friend Classes
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}

#endif // __VIOLET_ENGINE_SCENE_H_INCLUDED__
