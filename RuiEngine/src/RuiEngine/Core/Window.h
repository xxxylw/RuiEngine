#pragma once

#include "repch.h"

#include "RuiEngine/Core/Core.h"
#include "RuiEngine/Events/Event.h"

namespace RuiEngine {
	struct WindowProps
	{
		std::string Titile;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Rui Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Titile(title), Width(width), Height(height)
		{

		}
	};

	class RE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() { }

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}