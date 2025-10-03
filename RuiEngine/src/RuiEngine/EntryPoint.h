#pragma once

#ifdef RE_PLATFORM_WINDOWS

extern RuiEngine::Application* RuiEngine::CreateApplication();

int main(int argc, char** argv) {
	printf("RuiEngine\n");
	auto app = RuiEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // RE_PLATFORM_WINDOWS
