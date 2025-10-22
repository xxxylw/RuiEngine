#include "RuiEngine.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public RuiEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		/* Draw RuiEngine first Triangle */
		m_VertexArray.reset(RuiEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<RuiEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(RuiEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		RuiEngine::BufferLayout layout = {
				{ RuiEngine::ShaderDataType::Float3, "a_Position" },
				{ RuiEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<RuiEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(RuiEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);


		m_SquareVA.reset(RuiEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<RuiEngine::VertexBuffer> squareVB;
		squareVB.reset(RuiEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
				{ RuiEngine::ShaderDataType::Float3, "a_Position" }
			}
		);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<RuiEngine::IndexBuffer> squareIB;
		squareIB.reset(RuiEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				color = v_Color;
			}
		)";

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader.reset(new RuiEngine::Shader(vertexSrc, fragmentSrc));
		m_BlueShader.reset(new RuiEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
		/* End Draw */
	}

	void OnUpdate(RuiEngine::Timestep ts) override
	{
		/* polling here*/
		if (RuiEngine::Input::IsKeyPressed(RE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (RuiEngine::Input::IsKeyPressed(RE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		else if (RuiEngine::Input::IsKeyPressed(RE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (RuiEngine::Input::IsKeyPressed(RE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (RuiEngine::Input::IsKeyPressed(RE_KEY_LEFT))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (RuiEngine::Input::IsKeyPressed(RE_KEY_RIGHT))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		RuiEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RuiEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		RuiEngine::Renderer::BeginScene(m_Camera);

		RuiEngine::Renderer::Submit(m_BlueShader, m_SquareVA);
		RuiEngine::Renderer::Submit(m_Shader, m_VertexArray);

		RuiEngine::Renderer::EndScene();
	}

	void OnEvent(RuiEngine::Event& event) override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	private:
		std::shared_ptr<RuiEngine::Shader> m_Shader;
		std::shared_ptr<RuiEngine::VertexArray> m_VertexArray;
		
		std::shared_ptr<RuiEngine::Shader> m_BlueShader;
		std::shared_ptr<RuiEngine::VertexArray> m_SquareVA;

		RuiEngine::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 1.0f;
		
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public RuiEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
	
	}
};

RuiEngine::Application* RuiEngine::CreateApplication() {
	return new Sandbox();
}