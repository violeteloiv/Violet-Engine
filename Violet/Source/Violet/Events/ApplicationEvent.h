/////////////////
///
/// ApplicationEvent.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 1st, 2022
///
/// Contains Application related events and
/// functionality.
///
/////////////////

#ifndef __VIOLET_ENGINE_EVENTS_APPLICATION_H_INCLUDED__
#define __VIOLET_ENGINE_EVENTS_APPLICATION_H_INCLUDED__

#include "Violet/Events/Event.h"

namespace Violet
{
	/**
	 * @brief Passed through the event system when the window is resized.
	 * Stores information about new width amd height.
	 */
	class VIOLET_API WindowResizeEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a WindowResizeEvent object.
		 * @param p_Width The width being resized to.
		 * @param p_Height The height being resize to.
		 */
		WindowResizeEvent(unsigned int p_Width, unsigned int p_Height)
			: m_Width(p_Width), m_Height(p_Height)
		{

		}
	public: // Main Functionality
		/**
		 * @brief Gets the width being resized to.
		 * @returns The widrh being resized to.
		 */
		inline unsigned int GetWidth() const { return m_Width; }

		/**
		 * @brief Gets the height being resized to.
		 * @returns The height being resized to.
		 */
		inline unsigned int GetHeight() const { return m_Height; }
	public: // Overrides
		/**
		 * @brief Gives the Window Resize Event in the format:
		 *     - "WindowResizeEvent: {width}, {height}
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private: // Member Variables
		unsigned int m_Width, m_Height;
	};

	/**
	 * @brief Passed through the event system when the window is closed.
	 */
	class VIOLET_API WindowCloseEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a WindowCloseEvent object.
		 */
		WindowCloseEvent()
		{

		}
	public: // Macros
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @brief Passed through the event system when the application is ticked.
	 */
	class VIOLET_API AppTickEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a WindowCloseEvent object.
		 */
		AppTickEvent()
		{

		}
	public: // Macros
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @brief Passed through the event system when the application is updated.
	 */
	class VIOLET_API AppUpdateEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a AppUpdateEvent object.
		 */
		AppUpdateEvent()
		{

		}
	public: // Macros
		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * @brief Passed through the event system when a render pass is done.
	 */
	class VIOLET_API AppRenderEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a AppRenderEvent object.
		 */
		AppRenderEvent()
		{

		}
	public: // Macros
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}

#endif // __VIOLET_ENGINE_EVENTS_APPLICATION_H_INCLUDED__