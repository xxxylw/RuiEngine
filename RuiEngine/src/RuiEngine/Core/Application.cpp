#include "repch.h"
#include "Application.h"

#include "Input.h"

#include "RuiEngine/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace RuiEngine {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		RE_PROFILE_FUNCTION();

		RE_CORE_ASSERT(!s_Instance, "Application alredy exists!");
		s_Instance = this;

		m_Window = RuiEngine::Scope<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(true);

		Renderer::Init();
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		RE_PROFILE_FUNCTION();
	}

	void Application::PushLayer(Layer* layer)
	{
		RE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		RE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
	}

	// Handle all events in this func
	void Application::OnEvent(Event& e)
	{
		RE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		RE_PROFILE_FUNCTION();

		while (m_Running)
		{
			RE_PROFILE_SCOPE("Run Loop");

			float time = (float)glfwGetTime(); // For Temporary Platform::GetTime()
			Timestep timestep = time - m_LasetFrameTime;
			m_LasetFrameTime = time;

			if (!m_Minimized)
			{
				{
					RE_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}
			}

			m_ImGuiLayer->Begin();
			{
				RE_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RE_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}