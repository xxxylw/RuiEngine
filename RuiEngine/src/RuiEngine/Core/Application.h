#pragma once

#include "Core.h"

#include "Window.h"
#include "RuiEngine/Core/LayerStack.h"
#include "RuiEngine/Events/Event.h"
#include "RuiEngine/Events/ApplicationEvent.h"

#include "RuiEngine/ImGui/ImGuiLayer.h"

#include "RuiEngine/Core/Timestep.h"

namespace RuiEngine {

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			RE_CORE_ASSERT(index < Count, "Should : index < Count");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Hazel Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class RE_API Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		ApplicationSpecification m_Specification;

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
	Application* CreateApplication(ApplicationCommandLineArgs args);
}


