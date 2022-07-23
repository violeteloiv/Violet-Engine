/////////////////
///
/// MouseEvent.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 13rd, 2022
///
/// Contains Mouse related events and
/// functionality.
///
/////////////////

#ifndef __VIOLET_ENGINE_EVENTS_MOUSE_H_INCLUDED__
#define __VIOLET_ENGINE_EVENTS_MOUSE_H_INCLUDED__

#include "Violet/Core/MouseCodes.h"
#include "Violet/Events/Event.h"

namespace Violet
{
	/**
	 * @brief Passed through the event system when the mouse is moved.
	 * Stores information about the mouse position.
	 */
	class MouseMovedEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the MouseMovedEvent object.
		 * @param p_X The new mouseX position.
		 * @param p_Y The new mouseY position.
		 */
		MouseMovedEvent(const float p_X, const float p_Y)
			: m_MouseX(p_X), m_MouseY(p_Y)
		{

		}
	public: // Main Functionality
		/**
		 * @brief Gets the new mouseX position.
		 * @returns The new mouseX position.
		 */
		float GetX() const { return m_MouseX; }

		/**
		 * @brief Gest the new mouseY position.
		 * @returns The new mouseY position.
		 */
		float GetY() const { return m_MouseY; }
	public: // Overrides
		/**
		 * @brief Gives the Mouse Moved Event in the format:
		 *     - "MouseMovedEvent: {mouseX}, {mouseY}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private: // Member Variables
		float m_MouseX, m_MouseY;
	};

	/**
	 * @brief Passed through the event system when the mouse scroll wheel is used.
	 * Stores information about the scroll wheel position.
	 */
	class MouseScrolledEvent : public Event
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the MouseScrolledEvent object.
		 * @param p_XOffset The new scroll wheel X position.
		 * @param p_YOffset The new scroll wheen Y position.
		 */
		MouseScrolledEvent(const float p_XOffset, const float p_YOffset)
			: m_XOffset(p_XOffset), m_YOffset(p_YOffset)
		{

		}
	public: // Main Functionality
		/**
		 * @brief Gets the new X scroll wheel position.
		 * @returns The new X scroll wheel position.
		 */
		float GetXOffset() const { return m_XOffset; }
		
		/**
		 * @brief Gets the new Y scroll wheel position.
		 * @returns The new Y scroll wheel position.
		 */
		float GetYOffset() const { return m_YOffset; }
	public: // Overrides
		/**
		 * @brief Gives the Mouse Moved Event in the format:
		 *     - "MouseScrolledEvent: {xOffset}, {yOffset}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private: // Member Variables
		float m_XOffset, m_YOffset;
	};

	/**
	 * @brief Base class for different types of mouse button events.
	 */
	class MouseButtonEvent : public Event
	{
	public: // Main Functionality
		/**
		 * @brief Gets the mouse button being used.
		 * @returns The mouse button being used.
		 */
		MouseCode GetMouseButton() const { return m_Button; }
	public: // Macros
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected: // Constructors & Deconstructors
		/**
		 * @brief Constructs a MouseButtonEvent object.
		 * @param p_Button The button being used on the mouse.
		 */
		MouseButtonEvent(const MouseCode p_Button)
			: m_Button(p_Button)
		{

		}
	protected: // Protected Variables
		MouseCode m_Button;
	};

	/**
	 * @brief Passed through the event system when a mouse button is pressed.
	 * Stores information about the mouse button being pressed.
	 */
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a MouseButtonPressedEvent object.
		 * @param p_Button The button being pressed.
		 */
		MouseButtonPressedEvent(const MouseCode p_Button)
			: MouseButtonEvent(p_Button)
		{

		}
	public: // Overrides
		/**
		 * @brief Gives the Mouse Button Pressed Event in the format:
		 *     - "MouseButtonPressedEvent: {button_id}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/**
	 * @brief Passed through the event system when a mouse button is released.
	 * Stores information about the mouse button being released.
	 */
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs a MouseButtonReleasedEvent object.
		 * @param p_Button The button being released.
		 */
		MouseButtonReleasedEvent(const MouseCode p_Button)
			: MouseButtonEvent(p_Button)
		{

		}
	public: // Overrides
		/**
		 * @brief Gives the Mouse Button Released Event in the format:
		 *     - "MouseButtonReleasedEvent: {button_id}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

#endif // __VIOLET_ENGINE_EVENTS_MOUSE_H_INCLUDED__
