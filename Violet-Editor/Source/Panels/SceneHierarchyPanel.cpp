/////////////////
///
/// SceneHierarchyPanel.cpp
/// Violet McAllister
/// July 23rd, 2022
///
/// The Scene Hierarchy Panel in the Violet Editor
/// contains information regarding the entities in
/// a given scene.
/// 
/// This also allows the user to edit the components
/// in a given entity.
///
/////////////////

#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "Violet/Scene/Components.h"

namespace Violet
{
	/**
	 * @brief Constructs a Scene Hierarchy Panel.
	 * @param p_Context The context for which the panel
	 * belongs.
	 */
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& p_Context)
	{
		SetContext(p_Context);
	}

	/**
	 * @brief Sets the context for which the
	 * Scene Hierarchy Panel belongs.
	 * @param p_Context The context for which
	 * the panel belongs.
	 */
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& p_Context)
	{
		m_Context = p_Context;
	}

	/**
	 * @brief Responsible for actually drawing
	 * the ImGui panel.
	 */
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});

		ImGui::End();
	}

	/**
	 * @brief Draws a given entity to the panel.
	 * @param p_Entity The entity to be drawn.
	 */
	void SceneHierarchyPanel::DrawEntityNode(Entity p_Entity)
	{
		auto& tag = p_Entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == p_Entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)p_Entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = p_Entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}
}
