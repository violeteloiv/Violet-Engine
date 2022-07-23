/////////////////
///
/// Core.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 23rd, 2022
/// 
/// Defines the macros required to make dll
/// exporting work and connect the Violet
/// API to the Sandbox.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_H_INCLUDED__

#include <memory>

#include "Violet/Core/PlatformDetection.h"

#ifdef VT_DEBUG
	#if defined(VT_PLATFORM_WINDOWS)
		#define VT_DEBUGBREAK() __debugbreak()
	#elif defined(VT_PLATFORM_LINUX)
		#include <signal.h>
		#define VT_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif

	#define VT_ENABLE_ASSERTS
#else
	#define VT_DEBUGBREAK()
#endif

#ifdef VT_ENABLE_ASSERTS
	#define VT_ASSERT(x, ...) { if (!(x)) { VT_ERROR("Assertion Failed: {0}", __VA_ARGS__); VT_DEBUGBREAK(); } }
	#define VT_CORE_ASSERT(x, ...) { if (!(x)) { VT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); VT_DEBUGBREAK(); } }
#else
	#define VT_ASSERT(x, ...)
	#define VT_CORE_ASSERT(x, ...)
#endif // VT_ENABLE_ASSERTS

// Bit Operation
#define BIT(x) (1 << x)

// Event Bind Function
#define VT_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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
