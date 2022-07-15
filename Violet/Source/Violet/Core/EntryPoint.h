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
	VT_CORE_WARN("Initialized Logger!");
	int a = 5;
	VT_INFO("Hello! Var={0}", a);

	// Initialize Application
	auto app = Violet::CreateApplication();
	app->Run();
	delete app;
}

#endif // VT_PLATFORM_WINDOWS

#endif // __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__