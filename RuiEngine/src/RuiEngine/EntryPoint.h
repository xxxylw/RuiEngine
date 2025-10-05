#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RuiEngine::Application* RuiEngine::CreateApplication();

int main(int argc, char** argv) {

	RuiEngine::Log::Init();
	RE_CORE_ERROR("Initialized Core Log!");
	float a = 5.1;
	RE_TRACE("Hello Var = {0}", a);

	auto app = RuiEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // RE_PLATFORM_WINDOWS
