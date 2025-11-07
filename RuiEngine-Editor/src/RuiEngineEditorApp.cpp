#include "RuiEngine.h"

// ------Entry Point------
#include "RuiEngine/Core/EntryPoint.h"
// -----------------------

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "EditorLayer.h"
namespace RuiEngine {
	class RuiEngineEditor : public RuiEngine::Application {
	public:
		RuiEngineEditor() {
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~RuiEngineEditor() {

		}
	};

	Application* CreateApplication() {
		return new RuiEngineEditor();
	}
}
