/////////////////
///
/// SandboxApp.cpp
/// Violet McAllister
/// June 30th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include <Violet.h>

class SandboxApp : public Violet::Application
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}
}

Violet::Application* Violet::CreateApplication()
{
	return new SandboxApp();
}