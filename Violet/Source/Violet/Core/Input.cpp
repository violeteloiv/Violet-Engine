/////////////////
///
/// Input.cpp
/// Violet McAllister
/// July 15th, 2022
///
/// Used to conduct input polling on the application
/// and client side.
///
/////////////////

#include "vtpch.h"

#include "Violet/Core/Input.h"

#ifdef VT_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Violet
{
	Scope<Input> Input::s_Instance = Input::Create();

	/**
	 * @brief Allows the user to create an Input for the Windows
	 * system without specifically referencing Windows.
	 * @returns The windows input, not implemented for Windows.
	 */
	Scope<Input> Input::Create()
	{
	#ifdef VT_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
	#else
		VT_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
	#endif
	}
}