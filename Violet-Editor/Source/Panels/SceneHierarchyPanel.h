/////////////////
///
/// SceneHierarchyPanel.h
/// Violet McAllister
/// July 23rd, 2022
/// Updated: July 30th, 2022
///
/// The Scene Hierarchy Panel in the Violet Editor
/// contains information regarding the entities in
/// a given scene.
/// 
/// This also allows the user to edit the components
/// in a given entity.
///
/////////////////

#ifndef __VIOLET_EDITOR_PANELS_SCENE_HIERARCHY_PANEL_H_INCLUDED__
#define __VIOLET_EDITOR_PANELS_SCENE_HIERARCHY_PANEL_H_INCLUDED__

#include "Violet/Core/Base.h"
#include "Violet/Scene/Scene.h"
#include "Violet/Scene/Entity.h"

namespace Violet
{
	/**
	 * @brief Information regarding the entities
	 * in a scene.
	 */
	class SceneHierarchyPanel
	{
	public: // Constructors
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& p_Scene);
	public: // Main Functionality
		void SetContext(const Ref<Scene>& p_Scene);
	public: // Violet Internals
		void OnImGuiRender();
	public: // Getters
		/**
		 * @brief Gets the currently selected entity.
		 * @returns The currently selected entity.
		 */
		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private: // Helpers
		void DrawEntityNode(Entity p_Entity);
		void DrawComponents(Entity p_Entity);
	private: // Private Member Variables
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}

#endif // __VIOLET_EDITOR_PANELS_SCENE_HIERARCHY_PANEL_H_INCLUDED__
