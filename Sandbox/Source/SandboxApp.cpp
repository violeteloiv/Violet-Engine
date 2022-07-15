/////////////////
///
/// SandboxApp.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 15th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include <Violet.h>
#include <Violet/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class SandboxApp : public Violet::Application
{
public:
	SandboxApp()
	{
		PushLayer(new Sandbox2D());
		//PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};

Violet::Application* Violet::CreateApplication()
{
	return new SandboxApp();
}