/////////////////
///
/// Log.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 15th, 2022
///
/// Contains class information for logging. Utilizes
/// a static "singleton" like object in order to initialize
/// the logging objects. Otherwise uses macros in order to
/// log.
///
/////////////////

#ifndef __VIOLET_ENGINE_LOG_H_INCLUDED__
#define __VIOLET_ENGINE_LOG_H_INCLUDED__

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Violet/Core/Core.h"

namespace Violet
{
	/**
	 * @brief Defines the functionality of the logger object.
	 */
	class Log
	{
	public:
		static void Init();
	public:
		/**
		 * @brief Get the Core Logger object.
		 * 
		 * @return std::shared_ptr<spdlog::logger>& 
		 * @returns The core logger object.
		 */
		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		
		/**
		 * @brief Get the Client Logger object
		 * 
		 * @return std::shared_ptr<spdlog::logger>& 
		 * @returns The client logger object.
		 */
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define VT_CORE_TRACE(...)    	::Violet::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VT_CORE_INFO(...)     	::Violet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VT_CORE_WARN(...)     	::Violet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VT_CORE_ERROR(...)    	::Violet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VT_CORE_CRITICAL(...)   ::Violet::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VT_TRACE(...)	      	::Violet::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VT_INFO(...)	      	::Violet::Log::GetClientLogger()->info(__VA_ARGS__)
#define VT_WARN(...)	      	::Violet::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VT_ERROR(...)	      	::Violet::Log::GetClientLogger()->error(__VA_ARGS__)
#define VT_CRITICAL(...)	    ::Violet::Log::GetClientLogger()->critical(__VA_ARGS__) 

#endif // __VIOLET_ENGINE_LOG_H_INCLUDED__