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

#include <imgui/imgui.h>

class ExampleLayer : public Violet::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		if (Violet::Input::IsKeyPressed(VT_KEY_TAB))
			VT_TRACE("Tab Key Is Pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Text");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Violet::Event& p_Event) override
	{
		if (p_Event.GetEventType() == Violet::EventType::KeyPressed)
		{
			Violet::KeyPressedEvent& e = (Violet::KeyPressedEvent&)p_Event;
			if (e.GetKeyCode() == VT_KEY_TAB)
				VT_TRACE("Tab key is pressed (event)!");
			VT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class SandboxApp : public Violet::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};

Violet::Application* Violet::CreateApplication()
{
	return new SandboxApp();
}