/////////////////
///
/// Log.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 15th, 2022
///
/// Contains class implementations for the Log
/// object.
///
/////////////////

#include "vtpch.h"

#include "Violet/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Violet
{
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	/**
	 * @brief  
	 */
	void Log::Init()
	{
		// set the spdlog pattern
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// initialize core logger
		s_CoreLogger = spdlog::stdout_color_mt("VIOLET");
		s_CoreLogger->set_level(spdlog::level::trace);

		// initalize client logger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}