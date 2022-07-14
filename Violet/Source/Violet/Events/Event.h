/////////////////
///
/// Event.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 13th, 2022
///
/// Contains Event Types, Categories, and a Dispatcher.
/// 
/// Utilizes bit operations and bit masking in order to
/// create an event handler and dispatcher.
///
/////////////////

#ifndef __VIOLET_ENGINE_EVENTS_EVENT_H_INCLUDED__
#define __VIOLET_ENGINE_EVENTS_EVENT_H_INCLUDED__

#include "vtpch.h"

#include "Violet/Core/Core.h"

namespace Violet
{
	/**
	 * A set of values which denote all of the application events.
	 */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * A set of values which denote the category of the application event.
	 * Referred to with a normal enum so that multiple categories can be set at once.
	 * 
	 * None = (00000) = 0
	 * Input | Keyboard = (01100) = 12
	 * Input | Mouse | MouseButton = (01011) = 11
	 * 
	 * Using a bit operation like this makes it so that setting multiple categories
	 * end up as different values so that it doesn't overlap with a single category.
	 */
	enum EventCategory
	{
		None						= 0b00000,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	/**
	 * @brief A collection of functions that can be predetermined based on a given EventType. 
	 */
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								   virtual EventType GetEventType() const override { return GetStaticType(); }\
								   virtual const char* GetName() const override { return #type; }

	/**
	 * @brief A collection of functions that can be predetermined based on a give CategoryType. 
	 */
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/**
	 * @brief Defines the functionality of a Violet Event.
	 * 
	 * Event in Violet are currently blocking, meaning that when
	 * an event occurs it immediately gets dispatched and must be
	 * dealt with right then and there.
	 * 
	 * For the future, a better strategy might be to buffer events
	 * in an event bus and process them during the "event" part of
	 * the update stage.
	 * 
	 */
	class Event
	{
	public: // Main Functionality
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
	public: // Implemented Virtual
		/**
		 * @brief Basic ToString implementation for an Event.
		 * @returns The name of the event as a string.
		 */
		virtual std::string ToString() const 
		{ 
			return GetName(); 
		}
	public: // Implemented Inline
		/**
		 * @brief Checks if the provided category is within the current
		 * category flags.
		 * 
		 * This is done by comparing the current flags bit by bit. Lets say
		 * that we have input and keyboard flags, giving (01100). If we compare that
		 * to just input, anding them (01100) & (01000) we get (01000), or 8.
		 * 
		 * Since any non-zero number is considered "true" by C++, we can return this
		 * and if it returns a value, it's true, if it returns 0, it returns false.
		 * 
		 * @return Whether or not a category is in set category flags.
		 */
		inline bool IsInCategory(EventCategory p_Category)
		{
			return GetCategoryFlags() & p_Category;
		}
	public: // Public Member Variables
		bool Handled = false;
	};

	/**
	 * @brief The object which handles the events and determines
	 * which events are run at which time.
	 */
	class EventDispatcher
	{
	public: // Constructor & Deconstructor
		/**
		 * @brief Constructor for an EventDispatcher
		 * @param p_Event The event we are listening for.
		 */
		EventDispatcher(Event& p_Event)
			: m_Event(p_Event)
		{

		}
	public: // Main Functionality
		/**
		 * @brief When the event is triggered, runs the function passed in.
		 * F is deduced by the compiler during compilation.
		 * @param p_Function The event callback function.
		 * @returns Verification on if the even has successfully occured.
		 */
		template<typename T, typename F>
		bool Dispatch(const F& p_Function)
		{
			// If the type of the internal event is the same as the 
			// event passed through the dispatcher, run the event function.
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// Wizard Referencing & Dereferencing
				m_Event.Handled = p_Function(static_cast<T&>(m_Event));
				return true;
			}
			
			return false;
		}
	private: // Member Variables
		Event& m_Event;
	};

	/**
	 * @brief Operator overloading for outputing an event using c++ style printing.
	 * @param p_OutputStream The relevant output stream.
	 * @param p_Event The event to be printed.
	 */
	inline std::ostream& operator<<(std::ostream& p_OutputStream, const Event& p_Event)
	{
		return p_OutputStream << p_Event.ToString();
	}
}

#endif // __VIOLET_ENGINE_EVENTS_EVENT_H_INCLUDED__