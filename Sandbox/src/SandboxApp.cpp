#include "RuiEngine.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

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