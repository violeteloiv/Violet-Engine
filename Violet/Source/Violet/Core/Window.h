/////////////////
///
/// Window.h
/// Violet McAllister
/// July 1st, 2022
///
/// Contains Window Properties and a Window
/// interface to generalize window functionality
/// between systems.
///
/////////////////

#include "vtpch.h"

#include "Violet/Core/Core.h"
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
		unsigned int Width, Height;
	public: // Constructors & Deconstructors
		/**
		 * @brief Construcots a WindowProperties object.
		 * @param p_Title (default "Violet Engine") Is the title of the window created.
		 * @param p_Width (default 1280 pixels) Is the width of the window.
		 * @param p_Height (default 720 pixels) Is the height of the window.
		 */
		WindowProperties(const std::string& p_Title = "Violet Engine",
			unsigned int p_Width = 1280,
			unsigned int p_Height = 720)
			: Title(p_Title), Width(p_Width), Height(p_Height)
		{

		}
	};

	/**
	 * @brief An interface representing a desktop system based window. 
	 */
	class VIOLET_API Window
	{
	public: // Definitions
		using EventCallbackFunction = std::function<void(Event&)>;
	public: // Constructors & Deconstructors
		virtual ~Window() = default;
	public: // Main Functionality
		virtual void OnUpdate() = 0;
	public: // Getters
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	public: // Window Attributes
		virtual void SetEventCallback(const EventCallbackFunction& p_Callback) = 0;
		virtual void SetVSync(bool p_Enabled) = 0;
		virtual bool IsVSync() const = 0;
	public: // Static Creator
		static Window* Create(const WindowProperties& p_Properties = WindowProperties());
	};
}