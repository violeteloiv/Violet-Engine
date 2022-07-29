/////////////////
///
/// ImGuiLayer.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 28th, 2022
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
	class ImGuiLayer : public Layer
	{
	public: // Constructors & Deconstructors
		ImGuiLayer()
			: Layer("ImGuiLayer") { }
		~ImGuiLayer() = default;
	public: // Overrides
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& p_Event) override;
	public: // Main Functionality
		void Begin();
		void End();
	public: // Setters
		/**
		 * @brief Blocks ImGui events.
		 * @param p_Block Whether or not to block events.
		 */
		void BlockEvents(bool p_Block) { m_BlockEvents = p_Block; }
	public: // Themes
		void SetDarkThemeColors();
	private: // Private Member Variables
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};
}

#endif // __VIOLET_ENGINE_IMGUI_LAYER_H_INCLUDED__
