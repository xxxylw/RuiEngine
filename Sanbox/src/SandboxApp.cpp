#include "RuiEngine.h"


class Sandbox : public RuiEngine::Application {
public:
	Sandbox() {

	}

	~Sandbox() {
	
	}
};

RuiEngine::Application* RuiEngine::CreateApplication() {
	return new Sandbox();
}