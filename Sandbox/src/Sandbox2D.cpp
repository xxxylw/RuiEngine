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
	RE_PROFILE_FUNCTION();

	m_MaxVer = RuiEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	RE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(RuiEngine::Timestep ts)
{
	RE_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	RuiEngine::Renderer2D::ResetStats();
	{
		RE_PROFILE_SCOPE("Renderer Prep");
		RuiEngine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		RuiEngine::RenderCommand::Clear();
	}
	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		RE_PROFILE_SCOPE("Renderer Draw");

		RuiEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				RuiEngine::Renderer2D::DrawQuad({ x, y , -0.05}, { 0.45f, 0.45f }, color);
			}
		}
		RuiEngine::Renderer2D::EndScene();


		RuiEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		RuiEngine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		RuiEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		RuiEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		RuiEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_MaxVer, 10.0f);
		RuiEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_MaxVer, 20.0f);
		RuiEngine::Renderer2D::EndScene();

		
	}

}

void Sandbox2D::OnImGuiRender()
{
	RE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = RuiEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads:	%d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(RuiEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
