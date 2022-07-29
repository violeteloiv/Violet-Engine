/////////////////
///
/// Assert.h
/// Violet McAllister
/// July 24th, 2022
///
/// Allows asserting within Violet.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_ASSERT_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_ASSERT_H_INCLUDED__

#include <filesystem>

#include "Violet/Core/Base.h"
#include "Violet/Core/Log.h"

#ifdef VT_ENABLE_ASSERTS

	namespace Violet
	{
		namespace Assert
		{
			// Returns the simple file name rather than full path as suggested by LovelySanta
			constexpr const char* CurrentFileName(const char* p_Path) 
			{
				const char* file = p_Path;
				while (*p_Path)
				{
					if (*p_Path == '/' || *p_Path == '\\')
						file = ++p_Path;
					else
						p_Path++;
				}
				return file;
			}
		}
	}

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define VT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { VT##type##ERROR(msg, __VA_ARGS__); VT_DEBUGBREAK(); } }
	#define VT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) VT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define VT_INTERNAL_ASSERT_NO_MSG(type, check) VT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", VT_STRINGIFY_MACRO(check), ::Violet::Assert::CurrentFileName(__FILE__), __LINE__)

	#define VT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define VT_INTERNAL_ASSERT_GET_MACRO(...) VT_EXPAND_MACRO( VT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, VT_INTERNAL_ASSERT_WITH_MSG, VT_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define VT_ASSERT(...) VT_EXPAND_MACRO( VT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define VT_CORE_ASSERT(...) VT_EXPAND_MACRO( VT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define VT_ASSERT(...)
	#define VT_CORE_ASSERT(...)
#endif

#endif // __VIOLET_ENGINE_CORE_ASSERT_H_INCLUDED__
