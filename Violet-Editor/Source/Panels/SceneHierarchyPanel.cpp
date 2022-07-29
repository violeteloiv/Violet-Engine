/////////////////
///
/// SceneHierarchyPanel.cpp
/// Violet McAllister
/// July 23rd, 2022
/// Updated: July 28th, 2022
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
#include <imgui/imgui_internal.h>

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

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		// Right Click On Blank Space
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}
	
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
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)p_Entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = p_Entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(p_Entity);
			if (m_SelectionContext == p_Entity)
				m_SelectionContext = {};
		}
	}

	/**
	 * @brief Draws a control for a vec3 value.
	 * @param p_Label The label of the control.
	 * @param p_Values The values to control.
	 * @param p_ResetValue The value to reset the values to.
	 * @param p_ColumnWidth The width of the columns between values.
	 */
	static void DrawVec3Control(const std::string& p_Label, glm::vec3& p_Values, float p_ResetValue = 0.0f, float p_ColumnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(p_Label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, p_ColumnWidth);
		ImGui::Text(p_Label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			p_Values.x = p_ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &p_Values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			p_Values.y = p_ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &p_Values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			p_Values.z = p_ResetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &p_Values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	/**
	 * @brief Draws a component with all functionality.
	 * @param p_Name The name of the label for the component.
	 * @param p_Entity The entity the component belongs to.
	 * @param p_UIFunction The respective UI function attached.
	 */
	template<typename T, typename UIFunction>
	static void DrawComponent(const std::string& p_Name, Entity p_Entity, UIFunction p_UIFunction)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (p_Entity.HasComponent<T>())
		{
			auto& component = p_Entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, p_Name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				p_UIFunction(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				p_Entity.RemoveComponent<T>();
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
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("AddComponent");

		// Add Component Popup
		if (ImGui::BeginPopup("AddComponent"))
		{
			// Camera Component
			if (ImGui::MenuItem("Camera"))
			{
				m_SelectionContext.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			// Sprite Renderer Component
			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_SelectionContext.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();

		// Transform Component Drawing
		DrawComponent<TransformComponent>("Transform", p_Entity, [](auto& p_Component)
		{
			DrawVec3Control("Translation", p_Component.Translation);
			glm::vec3 rotation = glm::degrees(p_Component.Rotation);
			DrawVec3Control("Rotation", rotation);
			p_Component.Rotation = glm::radians(rotation);
			DrawVec3Control("Scale", p_Component.Scale, 1.0f);
		});

		// Camera Component
		DrawComponent<CameraComponent>("Camera", p_Entity, [](auto& p_Component)
		{
			auto& camera = p_Component.Camera;

			ImGui::Checkbox("Primary", &p_Component.Primary);

			const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
					if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
					{
						currentProjectionTypeString = projectionTypeStrings[i];
						camera.SetProjectionType((SceneCamera::ProjectionType)i);
					}

					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			// Perspective Camera Settings
			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
			{
				float perspectiveVerticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
				if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
					camera.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

				float perspectiveNear = camera.GetPerspectiveNearClip();
				if (ImGui::DragFloat("Near", &perspectiveNear))
					camera.SetPerspectiveNearClip(perspectiveNear);

				float perspectiveFar = camera.GetPerspectiveFarClip();
				if (ImGui::DragFloat("Far", &perspectiveFar))
					camera.SetPerspectiveFarClip(perspectiveFar);
			}

			// Orthographic Camera Settings
			if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
			{
				float orthoSize = camera.GetOrthographicSize();
				if (ImGui::DragFloat("Size", &orthoSize))
					camera.SetOrthographicSize(orthoSize);

				float orthoNear = camera.GetOrthographicNearClip();
				if (ImGui::DragFloat("Near", &orthoNear))
					camera.SetOrthographicNearClip(orthoNear);

				float orthoFar = camera.GetOrthographicFarClip();
				if (ImGui::DragFloat("Far", &orthoFar))
					camera.SetOrthographicFarClip(orthoFar);

				ImGui::Checkbox("Fixed Aspect Ratio", &p_Component.FixedAspectRatio);
			}
		});
		
		// Sprite Renderer Component Drawing
		DrawComponent<SpriteRendererComponent>("Sprite Renderer", p_Entity, [](auto& p_Component)
		{
			ImGui::ColorEdit4("Color", glm::value_ptr(p_Component.Color));
		});
	}
}
