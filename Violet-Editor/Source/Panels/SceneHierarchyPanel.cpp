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

#include <glm/gtc/type_ptr.hpp>

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
		// Scene Hierarchy Panel
		ImGui::Begin("Scene Hierarchy");
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});
		ImGui::End();
	
		// Properties Panel
		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);
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

	/**
	 * @brief Draws the components of a given entity.
	 * @param p_Entity The entity to fraw the components
	 * of.
	 */
	void SceneHierarchyPanel::DrawComponents(Entity p_Entity)
	{
		// Tag Component Drawing
		if (p_Entity.HasComponent<TagComponent>())
		{
			auto& tag = p_Entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		// Transform Component Drawing
		if (p_Entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = p_Entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}
		}
	}
}