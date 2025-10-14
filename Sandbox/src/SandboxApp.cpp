#include "RuiEngine.h"


class ExampleLayer : public RuiEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		/* polling here*/
		if (RuiEngine::Input::IsKeyPressed(RE_KEY_W))
			RE_TRACE("w key is pressed!(poll)");
	}

	void OnEvent(RuiEngine::Event& event) override
	{
		//RE_TRACE("ExampleLayer::OnEvent  {0}", event.ToString());
		if (event.GetEventType() == RuiEngine::EventType::KeyPressed)
		{
			RuiEngine::KeyPressedEvent& e = (RuiEngine::KeyPressedEvent&)event;
			RE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public RuiEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new RuiEngine::ImGuiLayer());
	}

	~Sandbox() {
	
	}
};

RuiEngine::Application* RuiEngine::CreateApplication() {
	return new Sandbox();
}