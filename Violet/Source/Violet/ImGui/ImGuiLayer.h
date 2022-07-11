/////////////////
///
/// ImGuiLayer.h
/// Violet McAllister
/// July 11th, 2022
///
/// Layer to display ImGui items. Defined by application, pushed to
/// LayerStack on client side.
///
/////////////////

#ifndef __VIOLET_ENGINE_IMGUI_LAYER_H_INCLUDED__
#define __VIOLET_ENGINE_IMGUI_LAYER_H_INCLUDED__

#include "Violet/Core/Layer.h"
#include "Violet/Events/ApplicationEvent.h"
#include "Violet/Events/KeyEvent.h"
#include "Violet/Events/MouseEvent.h"

namespace Violet
{
	/**
	 * @brief ImGuiLayer defined on the application side.
	 */
	class VIOLET_API ImGuiLayer : public Layer
	{
	public: // Constructors & Deconstructors
		ImGuiLayer()
			: Layer("ImGuiLayer") { }
		~ImGuiLayer() = default;
	public: // Main Functionality
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& p_Event);
	private: // Event Callbacks
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& p_Event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& p_Event);
		bool OnMouseMovedEvent(MouseMovedEvent& p_Event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& p_Event);
		bool OnKeyPressedEvent(KeyPressedEvent& p_Event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& p_Event);
		bool OnKeyTypedEvent(KeyTypedEvent& p_Event);
		bool OnWindowResizeEvent(WindowResizeEvent& p_Event);
	private: // Private Member Variables
		float m_Time = 0.0f;
	};
}

#endif // __VIOLET_ENGINE_IMGUI_LAYER_H_INCLUDED__