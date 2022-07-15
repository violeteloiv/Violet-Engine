/////////////////
///
/// Window.cpp
/// Violet McAllister
/// July 15th, 2022
///
/// Contains Window Properties and a Window
/// interface to generalize window functionality
/// between systems.
///
/////////////////

#include "vtpch.h"

#include "Violet/Core/Window.h"

#ifdef VT_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Violet
{
	/**
	 * @brief Allows the user to create a Window for the Windows
	 * system without specifically referencing Windows.
	 * @param p_Properties The window properties (title, width, height).
	 * @returns The windows window, not implemented for Windows.
	 */
	Scope<Window> Window::Create(const WindowProperties& p_Properties)
	{
	#ifdef VT_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(p_Properties);
	#else
		VT_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
	#endif
	}
}
