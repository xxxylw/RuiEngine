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
		RE_INFO("ExampleLayer::Update");
	}

	void OnEvent(RuiEngine::Event& event) override
	{
		RE_TRACE("ExampleLayer::OnEvent  {0}", event.ToString());
		event.Handled = true;
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