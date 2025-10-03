#pragma once

#include "Core.h"

namespace RuiEngine {

	class RE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/* To be defined in CLIENT */
	Application* CreateApplication();
}


