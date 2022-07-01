/////////////////
///
/// Core.h
/// Violet McAllister
/// June 30th, 2022
///
/// Defines the macros required to make dll
/// exporting work and connect the Violet
/// API to the Sandbox.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_H_INCLUDED__

#ifdef VT_PLATFORM_WINDOWS
	#ifdef VT_BUILD_DLL
		#define VIOLET_API __declspec(dllexport)
	#else
		#define VIOLET_API __declspec(dllimport)
	#endif // VT_BUILD_DLL
#else
	#error Violet Only Supports Windows
#endif // VT_PLATFORM_WINDOWS

// Bit Operation
#define BIT(x) (1 << x)

#endif // __VIOLET_ENGINE_CORE_H_INCLUDED__