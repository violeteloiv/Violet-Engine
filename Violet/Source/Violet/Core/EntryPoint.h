/////////////////
///
/// EntryPoint.h
/// Violet McAllister
/// June 30th, 2022
///
/// Allows the main function to be defined
/// and implemented on the engine side instead
/// of the client side.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__

#ifdef VT_PLATFORM_WINDOWS

extern Violet::Application* Violet::CreateApplication();

int main(int p_ArgumentCount, char** p_Arguments)
{
	auto app = Violet::CreateApplication();
	app->Run();
	delete app;
}

#endif // VT_PLATFORM_WINDOWS

#endif // __VIOLET_ENGINE_CORE_ENTRY_POINT_H_INCLUDED__