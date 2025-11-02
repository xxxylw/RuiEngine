#include "GameLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer()
	: Layer("GameLayer")
{
	auto& window = RuiEngine::Application::Get().GetWindow();
	CreateCamera(window.GetWidth(), window.GetHeight());

	Random::Init();
}

void GameLayer::OnAttach()
{
	m_Level.Init();

	ImGuiIO io = ImGui::GetIO();
	m_Font = io.Fonts->AddFontFromFileTTF("assets/OpenSans-Regular.ttf", 120.0f);
}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate(RuiEngine::Timestep ts)
{
	m_Time += ts;
	if ((int)(m_Time * 10.0f) % 8 > 4)
		m_Blink = !m_Blink;

	if (m_Level.IsGameOver())
		m_State = GameState::GameOver;

	const auto& playerPos = m_Level.GetPlayer().GetPosition();
	m_Camera->SetPosition({ playerPos.x, playerPos.y, 0.0f });

	switch (m_State)
	{
		case GameLayer::GameState::Play:
		{
			m_Level.OnUpdate(ts);
			break;
		}
	}

	// Render
	RuiEngine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1 });
	RuiEngine::RenderCommand::Clear();

	RuiEngine::Renderer2D::BeginScene(*m_Camera);
	m_Level.OnRender();
	RuiEngine::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	switch (m_State)
	{
		case GameLayer::GameState::Play:
		{
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetOverlayDrawList()->AddText(
				m_Font, 48.0f, ImGui::GetWindowPos(), IM_COL32(255, 255, 255, 255), scoreStr.c_str());
			break;
		}
		case GameLayer::GameState::MainMenu:
		{
			auto& pos = ImGui::GetWindowPos();
			auto width = RuiEngine::Application::Get().GetWindow().GetWidth();
			auto height = RuiEngine::Application::Get().GetWindow().GetHeight();

			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
			{
				ImGui::GetOverlayDrawList()->AddText(
					m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");
				break;
			}
		}
		case GameLayer::GameState::GameOver:
		{
			auto pos = ImGui::GetWindowPos();
			auto width = RuiEngine::Application::Get().GetWindow().GetWidth();
			auto height = RuiEngine::Application::Get().GetWindow().GetHeight();
			pos.x += width * 0.5f - 300.0f;
			pos.y += 50.0f;
			if (m_Blink)
				ImGui::GetOverlayDrawList()->AddText(m_Font, 120.0f, pos, 0xffffffff, "Click to Play!");

			pos.x += 200.0f;
			pos.y += 150.0f;
			uint32_t playerScore = m_Level.GetPlayer().GetScore();
			std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
			ImGui::GetOverlayDrawList()->AddText(m_Font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
			break;
		}
	}
}

void GameLayer::OnEvent(RuiEngine::Event& e)
{
	RuiEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<RuiEngine::WindowResizeEvent>(RE_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<RuiEngine::MouseButtonPressedEvent>(RE_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(RuiEngine::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(RuiEngine::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
	float aspectRatio = (float)width / height;

	float camWidth = 8.0f;
	float bottom = -camWidth;
	float top = camWidth;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;
	m_Camera = RuiEngine::CreateScope<RuiEngine::OrthographicCamera>(left, right, bottom, top);
}
