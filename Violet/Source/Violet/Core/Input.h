/////////////////
///
/// Input.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 17th, 2022
///
/// Used to conduct input polling on the application
/// and client side.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__

#include "Violet/Core/Base.h"
#include "Violet/Core/KeyCodes.h"
#include "Violet/Core/MouseCodes.h"

namespace Violet
{
	/**
	 * @brief Main input object for Input Polling in
	 * Violet.
	 */
	class Input
	{
	public: // Main Functionality
		static bool IsKeyPressed(KeyCode p_Key);
		static bool IsMouseButtonPressed(MouseCode p_Button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}

#endif // __VIOLET_ENGINE_CORE_INPUT_H_INCLUDED__