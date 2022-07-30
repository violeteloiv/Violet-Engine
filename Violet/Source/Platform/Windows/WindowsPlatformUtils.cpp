/////////////////
///
/// WindowsPlatformUtils.cpp
/// Violet McAllister
/// July 29th, 2022
/// Updated: July 30th, 2022
///
/// A windows implementation of all
/// platform specific utility funcitons.
///
/////////////////

#include "vtpch.h"

#include "Violet/Utils/PlatformUtils.h"

#include <commdlg.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 // Native GLFW Functions
#include <GLFW/glfw3native.h>

#include "Violet/Core/Application.h"

namespace Violet
{
	/**
	 * @brief Opens a file dialog specifically for opening a file.
	 * Aparam p_Filter The filter for which files are allowed to
	 * be opened.
	 * @returns The filepath to the selected file in the open
	 * file dialog.
	 */
	std::optional<std::string> FileDialogs::OpenFile(const char* p_Filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = p_Filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

		if (GetOpenFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::nullopt;
	}

	/**
	 * @brief Opens a file dialog specifically for saving a file.
	 * Aparam p_Filter The filter for which files are allowed to
	 * be saved.
	 * @returns The filepath to the selected file in the save
	 * file dialog.
	 */
	std::optional<std::string> FileDialogs::SaveFile(const char* p_Filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow());
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = p_Filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter.
		ofn.lpstrDefExt = strchr(p_Filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::nullopt;
	}
}
