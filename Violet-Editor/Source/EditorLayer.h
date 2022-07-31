/////////////////
///
/// EditorLayer.h
/// Violet McAllister
/// July 17th, 2022
/// Updated: July 30th, 2022
///
/// The main editor layer for Violet Editor.
///
/////////////////

#ifndef __VIOLET_EDITOR_LAYER_H_INCLUDED__
#define __VIOLET_EDITOR_LAYER_H_INCLUDED__

#include "Violet.h"

#include "Violet/Renderer/EditorCamera.h"

#include "Panels/SceneHierarchyPanel.h"

namespace Violet {

	/**
	 * @brief Contains all the main layer information
	 * for the Violet-Editor.
	 */
	class EditorLayer : public Layer
	{
	public: // Constructors & Deconstructprs
		EditorLayer();
		virtual ~EditorLayer() = default;
	public: // Main Functionality
		virtual void OnAttach() override;
		virtual void OnDetach() override;
	public: // Update/Event
		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private: // Event
		bool OnKeyPressed(KeyPressedEvent& p_Event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& p_Event);
	private: // File Dialogs
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private: // Private Member Variables
		OrthographicCameraController m_CameraController;
		Ref<Texture2D> m_CheckerboardTexture;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		int m_GizmoType = -1;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];
		EditorCamera m_EditorCamera;
		Entity m_HoveredEntity;
	private: // Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	private: // Temporary
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;
		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;
	};
}

#endif // __VIOLET_EDITOR_LAYER_H_INCLUDED__
