/////////////////
///
/// SandboxApp.cpp
/// Violet McAllister
/// June 30th, 2022
/// Updated: July 11th, 2022
///
/// Testing Violet API Code
///
/////////////////

#include <Violet.h>

class ExampleLayer : public Violet::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		VT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Violet::Event& p_Event) override
	{
		VT_TRACE("{0}", p_Event);
	}
};

class SandboxApp : public Violet::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Violet::ImGuiLayer());
	}

	~SandboxApp()
	{

	}
};

Violet::Application* Violet::CreateApplication()
{
	return new SandboxApp();
}