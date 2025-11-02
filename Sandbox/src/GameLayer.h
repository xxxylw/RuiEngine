#pragma once

#include "RuiEngine.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public RuiEngine::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(RuiEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(RuiEngine::Event& e) override;

	bool OnMouseButtonPressed(RuiEngine::MouseButtonPressedEvent& e);
	bool OnWindowResize(RuiEngine::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	RuiEngine::Scope<RuiEngine::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time = 0.0f;
	bool m_Blink = false;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};

	GameState m_State = GameState::MainMenu;

};