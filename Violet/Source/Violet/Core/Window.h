/////////////////
///
/// Window.h
/// Violet McAllister
/// July 1st, 2022
/// Updated: July 28th, 2022
///
/// Contains Window Properties and a Window
/// interface to generalize window functionality
/// between systems.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_WINDOW_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_WINDOW_H_INCLUDED__

#include <sstream>

#include "Violet/Core/Base.h"
#include "Violet/Events/Event.h"

namespace Violet
{
	/**
	 * @brief The collection of data needed to create a window.
	 */
	struct WindowProperties
	{
	public: // Public Member Variables
		std::string Title;
		uint32_t Width, Height;
	public: // Constructors & Deconstructors
		/**
		 * @brief Construcots a WindowProperties object.
		 * @param p_Title (default "Violet Engine") Is the title of the window created.
		 * @param p_Width (default 1280 pixels) Is the width of the window.
		 * @param p_Height (default 720 pixels) Is the height of the window.
		 */
		WindowProperties(const std::string& p_Title = "Violet Engine",
			uint32_t p_Width = 1600,
			uint32_t p_Height = 900)
			: Title(p_Title), Width(p_Width), Height(p_Height)
		{

		}
	};

	/**
	 * @brief An interface representing a desktop system based window. 
	 */
	class Window
	{
	public: // Definitions
		using EventCallbackFunction = std::function<void(Event&)>;
	public: // Constructors & Deconstructors
		virtual ~Window() = default;
	public: // Main Functionality
		virtual void OnUpdate() = 0;
	public: // Getters
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;
	public: // Window Attributes
		virtual void SetEventCallback(const EventCallbackFunction& p_Callback) = 0;
		virtual void SetVSync(bool p_Enabled) = 0;
		virtual bool IsVSync() const = 0;
	public: // Static Creator
		static Scope<Window> Create(const WindowProperties& p_Properties = WindowProperties());
	};
}

#endif // __VIOLET_ENGINE_CORE_WINDOW_H_INCLUDED__
