#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RuiEngine::Application* RuiEngine::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv) {

	RuiEngine::Log::Init();

	RE_PROFILE_BEGIN_SESSION("Startup", "RuiEngineProfile-Startup.json");
	auto app = RuiEngine::CreateApplication({ argc, argv });
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("Runtime", "RuiEngineProfile-Runtile.json");
	app->Run();
	RE_PROFILE_END_SESSION();

	RE_PROFILE_BEGIN_SESSION("Shutdown", "RuiEngineProfile-Shutdown.json");
	delete app;
	RE_PROFILE_END_SESSION();
}

#endif // RE_PLATFORM_WINDOWS
