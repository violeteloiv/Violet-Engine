/////////////////
///
/// EditorLayer.h
/// Violet McAllister
/// July 17th, 2022
///
/// The main editor layer for Violet Editor.
///
/////////////////

#include "Violet.h"

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
	private: // Private Member Variables
		OrthographicCameraController m_CameraController;
		Ref<Texture2D> m_CheckerboardTexture;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	private: // Temporary
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;
	};
}