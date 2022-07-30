/////////////////
///
/// PlatformUtils.h
/// Violet McAllister
/// July 29th, 2022
///
/// Functionality regarding utilities that may
/// be platform specific in nature, such as file
/// dialogs.
///
/////////////////

#ifndef __VIOLET_ENGINE_UTILS_PLATFORM_UTILS_H_INCLUDED__
#define __VIOLET_ENGINE_UTILS_PLATFORM_UTILS_H_INCLUDED__

#include <string>

namespace Violet
{
	/**
	 * @brief Contains information for dealing with a
	 * native filesystem.
	 */
	class FileDialogs
	{
	public:
		static std::string OpenFile(const char* p_Filter);
		static std::string SaveFile(const char* p_Filter);
	};
}

#endif // __VIOLET_ENGINE_UTILS_PLATFORM_UTILS_H_INCLUDED__
