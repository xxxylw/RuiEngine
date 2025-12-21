#include "RuiEngine.h"

// ------Entry Point------
#include "RuiEngine/Core/EntryPoint.h"
// -----------------------

#include "EditorLayer.h"
namespace RuiEngine {
	class RuiEngineEditor : public RuiEngine::Application
	{
	public:
		RuiEngineEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~RuiEngineEditor() {

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "RuiEngineEditor";
		spec.CommandLineArgs = args;

		return new RuiEngineEditor(spec);
	}
}
