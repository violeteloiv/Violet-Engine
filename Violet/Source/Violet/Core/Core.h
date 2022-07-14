/////////////////
///
/// Core.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 13th, 2022
/// 
/// Defines the macros required to make dll
/// exporting work and connect the Violet
/// API to the Sandbox.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_H_INCLUDED__

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define VT_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define VT_PLATFORM_IOS
	#error "IOS is not supported!"
		#elif TARGET_OS_MAC == 1
	#define VT_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define VT_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define VT_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef VT_PLATFORM_WINDOWS
	#if VT_DYNAMIC_LINK
		#ifdef VT_BUILD_DLL
			#define VIOLET_API __declspec(dllexport)
		#else
			#define VIOLET_API __declspec(dllimport)
		#endif // VT_BUILD_DLL
	#else
		#define VIOLET_API
	#endif // VT_DYNAMIC_LINK
#else
	#error Violet Only Supports Windows
#endif // VT_PLATFORM_WINDOWS

#ifdef VT_ENABLE_ASSERTS
	#define VT_ASSERT(x, ...) { if (!(x)) { VT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VT_CORE_ASSERT(x, ...) { if (!(x)) { VT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VT_ASSERT(x, ...)
	#define VT_CORE_ASSERT(x, ...)
#endif // VT_ENABLE_ASSERTS

// Bit Operation
#define BIT(x) (1 << x)

// Event Bind Function
#define VT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Violet
{
	/**
	 * @brief Scopes essentially contain a pointer to one
	 * place in memory only, with the perk that once there
	 * are no more references to that place in memory it
	 * gets deallocated.
	 */
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	/**
	 * @brief Refs are similar to Scopes except that multiple
	 * references can be made to that place in memory, with the
	 * same perk that once there are no more references to that
	 * place in memory it gets deallocated.
	 */
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#endif // __VIOLET_ENGINE_CORE_H_INCLUDED__