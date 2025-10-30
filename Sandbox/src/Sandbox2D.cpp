#include "Sandbox2D.h"
#include "RuiEngine.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_MaxVer = RuiEngine::Texture2D::Create("assets/textures/fomula1.jpg");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(RuiEngine::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	RuiEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	RuiEngine::RenderCommand::Clear();

	RuiEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	RuiEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 0.2f, 0.2f, 0.3f, 1.0f });
	RuiEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 1.0f }, { 0.5f, 0.8f, 0.3f, 1.0f });
	RuiEngine::Renderer2D::DrawQuad({ 1.0f, 1.0f, -0.5f }, { 10.0f, 10.0f }, m_MaxVer);
	RuiEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(RuiEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
