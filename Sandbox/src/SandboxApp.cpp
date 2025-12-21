#include "RuiEngine.h"

// ------Entry Point------
#include "RuiEngine/Core/EntryPoint.h"
// -----------------------

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "Sandbox2D.h"

class Sandbox : public RuiEngine::Application {
public:
	Sandbox(const RuiEngine::ApplicationSpecification& specification)
		: RuiEngine::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {
	
	}
};

RuiEngine::Application* RuiEngine::CreateApplication(RuiEngine::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../RuiEngine-Editor";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}