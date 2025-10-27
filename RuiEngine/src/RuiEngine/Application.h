#pragma once

#include "Core.h"

#include "Window.h"
#include "RuiEngine/LayerStack.h"
#include "RuiEngine/Events/Event.h"
#include "RuiEngine/Events/ApplicationEvent.h"

#include "RuiEngine/ImGui/ImGuiLayer.h"

#include "RuiEngine/Core/Timestep.h"

namespace RuiEngine {

	class RE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		RuiEngine::Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		Timestep m_Timestep;
		float m_LasetFrameTime = 0.0f;
		bool m_Minimized = false;

	private:
		static Application* s_Instance;
	};

	/* To be defined in CLIENT */
	Application* CreateApplication();
}


