#pragma once

#include "RuiEngine.h"

class ExampleLayer : public RuiEngine::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(RuiEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(RuiEngine::Event& e) override;
private:
	RuiEngine::ShaderLibrary m_ShaderLibrary;
	RuiEngine::Ref<RuiEngine::Shader> m_Shader;
	RuiEngine::Ref<RuiEngine::VertexArray> m_VertexArray;

	RuiEngine::Ref<RuiEngine::Shader> m_FlatColorShader;
	RuiEngine::Ref<RuiEngine::VertexArray> m_SquareVA;

	RuiEngine::Ref<RuiEngine::Texture2D> m_Texture, m_TextureHat;

	RuiEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};
