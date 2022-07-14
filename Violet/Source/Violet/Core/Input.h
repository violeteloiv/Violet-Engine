/////////////////
///
/// Input.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 13th, 2022
///
/// Used to conduct input polling on the application
/// and client side.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__

#include "Violet/Core/Core.h"

namespace Violet
{
	/**
	 * @brief Main input object for Input Polling in
	 * Violet.
	 */
	class Input
	{
	protected: // Constructor For Singleton
		Input() = default;
	public: // Constructors For Singleton
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
	public: // Static Key Events
		/**
		 * @brief Checks if a certain key is pressed.
		 * @param p_KeyCode The key code of the key we're checking.
		 * @returns If a certain key is being pressed.
		 */
		inline static bool IsKeyPressed(int p_KeyCode) { return s_Instance->IsKeyPressedImpl(p_KeyCode); }
	public: // Static Mouse Events
		/**
		 * @brief Checks if a mouse button is pressed.
		 * @param p_Button the button code of the button we are checking.
		 * @returns If a certain mouse butotn is being pressed.
		 */
		inline static bool IsMouseButtonPressed(int p_Button) { return s_Instance->IsMouseButtonPressedImpl(p_Button); }

		/**
		 * @brief Gets the mouse position.
		 * @returns The mouse position as a std::pair
		 */
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }

		/**
		 * @brief Gets the mouse X position.
		 * @returns The mouse X position.
		 */
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		/*
		 * @brief Gets the mouse Y position.
		 * @returns The mouse Y position.
		 */
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected: // Key Event Implementations
		virtual bool IsKeyPressedImpl(int p_KeyCode) = 0;
	protected: // Mouse Event Implementations
		virtual bool IsMouseButtonPressedImpl(int p_Button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private: // Static Instance
		static Input* s_Instance;
	};
}

#endif // __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__