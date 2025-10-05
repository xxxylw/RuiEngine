#include "repch.h"
#include "Application.h"
#include "RuiEngine/Events/ApplicationEvent.h"
#include "RuiEngine/Log.h"

namespace RuiEngine {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			RE_TRACE(e.ToString());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			RE_TRACE(e.ToString());
		}
		while (true);
	}
}