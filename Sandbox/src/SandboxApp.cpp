#include "RuiEngine.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
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
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				v_Position = gl_Position.xyz;
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_Shader.reset(RuiEngine::Shader::Create(vertexSrc, fragmentSrc));
		m_FlatColorShader.reset(RuiEngine::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<RuiEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<RuiEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				RuiEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		RuiEngine::Renderer::Submit(m_Shader, m_VertexArray);

		RuiEngine::Renderer::EndScene();
	}

	void OnEvent(RuiEngine::Event& event) override
	{
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	private:
		std::shared_ptr<RuiEngine::Shader> m_Shader;
		std::shared_ptr<RuiEngine::VertexArray> m_VertexArray;
		
		std::shared_ptr<RuiEngine::Shader> m_FlatColorShader;
		std::shared_ptr<RuiEngine::VertexArray> m_SquareVA;

		RuiEngine::OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition;
		float m_CameraMoveSpeed = 1.0f;
		
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;

		glm::vec3 m_SquareColor = { 0.2f, 0.4f, 0.8f };
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