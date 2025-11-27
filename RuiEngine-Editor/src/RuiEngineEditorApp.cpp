#include "RuiEngine.h"

// ------Entry Point------
#include "RuiEngine/Core/EntryPoint.h"
// -----------------------

#include "EditorLayer.h"
namespace RuiEngine {
	class RuiEngineEditor : public RuiEngine::Application
	{
	public:
		RuiEngineEditor(ApplicationCommandLineArgs args)
			: Application("Hazelnut", args)
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~RuiEngineEditor() {

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new RuiEngineEditor(args);
	}
}
