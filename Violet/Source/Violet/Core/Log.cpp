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

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Violet
{
	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	/**
	 * @brief Initializes the logger and file logging
	 * systems.
	 */
	void Log::Init()
	{
		// Setup Log Sinks
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Violet.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		// Setup Core Logger
		s_CoreLogger = std::make_shared<spdlog::logger>("HAZEL", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		// Setup Client Logger
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}
}