#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RuiEngine::Application* RuiEngine::CreateApplication();

int main(int argc, char** argv) {

	RuiEngine::Log::Init();

	RE_PROFILE_BEGIN_SESSION("Startup", "RuiEngineProfile-Startup.json");
	auto app = RuiEngine::CreateApplication();
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("Runtime", "RuiEngineProfile-Runtile.json");
	app->Run();
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("Runtime", "RuiEngineProfile-Shutdown.json");
	delete app;
	RE_PROFILE_END_SESSION();
}

#endif // RE_PLATFORM_WINDOWS
