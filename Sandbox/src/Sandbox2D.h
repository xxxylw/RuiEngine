#pragma once

#include "RuiEngine.h"

#include "ParticleSystem.h"

class Sandbox2D : public RuiEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(RuiEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(RuiEngine::Event& e) override;

private:
	RuiEngine::OrthographicCameraController m_CameraController;

	//Temp
	RuiEngine::Ref<RuiEngine::VertexArray> m_SquareVA;
	RuiEngine::Ref<RuiEngine::Shader> m_FlatColorShader;
	RuiEngine::Ref<RuiEngine::Texture2D> m_MaxVer;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;
};