/////////////////
///
/// KeyEvent.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 11th, 2022
///
/// Contains Keyboard related events and
/// functionality.
///
/////////////////

#ifndef __VIOLET_ENGINE_EVENTS_KEY_H_INCLUDED__
#define __VIOLET_ENGINE_EVENTS_KEY_H_INCLUDED__

#include "Event.h"

namespace Violet
{
	/**
	 * @brief Base class for different types of key event.
	 */
	class KeyEvent : public Event
	{
	public: // Main Functionality
		/**
		 * @brief Gets the key code of the event.
		 * @returns The key code of the event.
		 */
		inline int GetKeyCode() const { return m_KeyCode; }
	public: // Macros
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the KeyEvent object.
		 * @param p_KeyCode The keycode of the non-specific key event.
		 */
		KeyEvent(int p_KeyCode)
			: m_KeyCode(p_KeyCode)
		{

		}
	protected: // Protected Variables
		int m_KeyCode;
	};

	/**
	 * @brief Passed through the event system when a key is pressed.
	 * Stores information about the key code and repeat count.
	 */
	class KeyPressedEvent : public KeyEvent
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the KeyPressedEvent object.
		 * @param p_KeyCode The keycode of the key being pressed.
		 * @param p_RepeatCount The number of times the key press has been repeated.
		 */
		KeyPressedEvent(int p_KeyCode, int p_RepeatCount)
			: KeyEvent(p_KeyCode), m_RepeatCount(p_RepeatCount)
		{

		}
	public: // Main Functionality
		/**
		 * @brief Gets the amount of times a key has been repeated.
		 * @returns the number of times repeated.
		 */
		inline int GetRepeatCount() const { return m_RepeatCount; }
	public: // Override
		/**
		 * @brief Gives the Key Pressed Event in the format:
		 *     - "KeyPressedEvent: {keycode} ({repeat_count} repeats)"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(KeyPressed)
	private: // Member Variables
		int m_RepeatCount;
	};

	/**
	 * @brief Passed through the event system when the key is released.
	 * Stores information about the key code.
	 */
	class KeyReleasedEvent : public KeyEvent
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the KeyReleasedEvent object.
		 * @param p_KeyCode They key code of the button released.
		 */
		KeyReleasedEvent(int p_KeyCode)
			: KeyEvent(p_KeyCode)
		{

		}
	public: // Overrides
		/**
		 * @brief Gives the Key Released Event in the format:
		 *     - "KeyReleasedEvent: {keycode}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(KeyReleased)
	};

	/**
	 * @brief Passed through the event system when keys are typed.
	 * Stores information about the key code.
	 */
	class KeyTypedEvent : public KeyEvent
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructor for the KeyTypedEvent object.
		 * @param p_KeyCode They key code of the button pressed.
		 */
		KeyTypedEvent(int p_KeyCode)
			: KeyEvent(p_KeyCode)
		{

		}
	public: // Overrides
		/**
		 * @brief Gives the Key Typed Event in the format:
		 *     - "KeyTypedEvent: {keycode}"
		 * @returns The above string formatted.
		 */
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	public: // Macros
		EVENT_CLASS_TYPE(KeyTyped)
	};
}

#endif // __VIOLET_ENGINE_EVENTS_KEY_H_INCLUDED__