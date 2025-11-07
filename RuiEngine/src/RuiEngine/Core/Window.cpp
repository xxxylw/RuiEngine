#include "repch.h"
#include "RuiEngine/Core/Window.h"

#ifdef RE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace RuiEngine {
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef RE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		RE_CORE_ASSERT(false, "Unknow platform!");
#endif
	}
}