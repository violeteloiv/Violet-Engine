/////////////////
///
/// EntryPoint.h
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 15th, 2022
///
/// Allows the main function to be defined
/// and implemented on the engine side instead
/// of the client side.
///
/// Initializes Logging.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__

#ifdef VT_PLATFORM_WINDOWS

#include "Violet/Core/Core.h"

extern Violet::Application* Violet::CreateApplication();

int main(int p_ArgumentCount, char** p_Arguments)
{
	// Initialize Logger
	Violet::Log::Init();

	// Initialize Application
	VT_PROFILE_BEGIN_SESSION("Startup", "VioletProfile-Startup.json");
	auto app = Violet::CreateApplication();
	VT_PROFILE_END_SESSION();

	VT_PROFILE_BEGIN_SESSION("Runtime", "VioletProfile-Runtime.json");
	app->Run();
	VT_PROFILE_END_SESSION();

	VT_PROFILE_BEGIN_SESSION("Shutdown", "VioletProfile-Shutdown.json");
	delete app;
	VT_PROFILE_END_SESSION();
}

#endif // VT_PLATFORM_WINDOWS

#endif // __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__