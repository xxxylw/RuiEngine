#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RuiEngine::Application* RuiEngine::CreateApplication();

int main(int argc, char** argv) {

	RuiEngine::Log::Init();
	RE_CORE_ERROR("Initialized Core Log!");

	auto app = RuiEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // RE_PLATFORM_WINDOWS
