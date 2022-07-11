/////////////////
///
/// WindowsWindow.h
/// Violet McAllister
/// July 1st, 2022
///
/// Using the generalized Window class we create
/// a WindowsWindow definition to specify the implementation
/// for a Windows system using GLFW.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORM_WINDOWS_WINDOW_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_WINDOWS_WINDOW_H_INCLUDED__

#include <GLFW/glfw3.h>

#include "Violet/Core/Window.h"

namespace Violet
{
	/**
	 * @brief Defines what a WindowsWindow consists of using GLFW.
	 */
	class WindowsWindow : public Window
	{
	public: // Constructors & Deconstructors
		WindowsWindow(const WindowProperties& p_Properties);
		virtual ~WindowsWindow();
	public: // Override Implementations
		/**
		 * @brief Gets the width of a windows window.
		 * @returns The width of a windows window.
		 */
		inline unsigned int GetWidth() const override { return m_Data.Width; }

		/**
		 * @brief Gets the height of a windows window.
		 * @returns The height of a windows window.
		 */
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		/**
		 * @brief Sets a given event callback for the window.
		 * @param p_Callback The callback for the event.
		 */
		inline void SetEventCallback(const EventCallbackFunction& p_Callback) override { m_Data.EventCallback = p_Callback; }
	public: // Override Definitions
		void OnUpdate() override;
		void SetVSync(bool p_Enabled) override;
		bool IsVSync() const override;
	private: // Initializer & Shutdown
		virtual void Init(const WindowProperties& p_Properties);
		virtual void Shutdown();
	private: // WindowData
		/**
		 * @brief The data needed to use a Windows Window. 
		 */
		struct WindowData
		{
		public: // Public Member Variables
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFunction EventCallback;
		};
	private: // Private Member Variables
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_WINDOWS_WINDOW_H_INCLUDED__