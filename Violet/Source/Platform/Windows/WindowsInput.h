/////////////////
///
/// WindowsInput.h
/// Violet McAllister
/// July 11th, 2022
///
/// Windows Implementation of the Input object.
///
/////////////////

#ifndef __VIOLET_ENGINE_PLATFORM_WINDOWS_INPUT_H_INCLUDED__
#define __VIOLET_ENGINE_PLATFORM_WINDOWS_INPUT_H_INCLUDED__

#include "Violet/Core/Input.h"

namespace Violet
{
	/**
	 * @brief Windows Implementation of the Input class.
	 */
	class WindowsInput : public Input
	{
	protected: // Key Event Implementations
		virtual bool IsKeyPressedImpl(int p_KeyCode) override;
	protected: // Mouse Event Implementations
		virtual bool IsMouseButtonPressedImpl(int p_Button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}

#endif // __VIOLET_ENGINE_PLATFORM_WINDOWS_INPUT_H_INCLUDED__