#include <BrickEngine.h>
#include "BrickEngine/Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"

class ExampleLayer : public BrickEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(BrickEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<BrickEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(BrickEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		BrickEngine::BufferLayout layout = {
			{ BrickEngine::ShaderDataType::Float3, "a_Position" },
			{ BrickEngine::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<BrickEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(BrickEngine::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(BrickEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<BrickEngine::VertexBuffer> squareVB;
		squareVB.reset(BrickEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ BrickEngine::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<BrickEngine::IndexBuffer> squareIB;
		squareIB.reset(BrickEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec4 v_Color;
			
			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(BrickEngine::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(BrickEngine::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	virtual void OnUpdate(BrickEngine::Timestep ts) override
	{
		if (BrickEngine::Input::IsKeyPressed(BRICKENGINE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		if (BrickEngine::Input::IsKeyPressed(BRICKENGINE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;
		if (BrickEngine::Input::IsKeyPressed(BRICKENGINE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;
		if (BrickEngine::Input::IsKeyPressed(BRICKENGINE_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;

		BrickEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		BrickEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		BrickEngine::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<BrickEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<BrickEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				BrickEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		BrickEngine::Renderer::Submit(m_Shader, m_VertexArray);

		BrickEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settngs");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(BrickEngine::Event& event) override
	{
	}
private:
	std::shared_ptr<BrickEngine::Shader> m_Shader;
	std::shared_ptr<BrickEngine::VertexArray> m_VertexArray;

	std::shared_ptr<BrickEngine::Shader> m_FlatColorShader;
	std::shared_ptr<BrickEngine::VertexArray> m_SquareVA;

	BrickEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 5.0f;

	float m_CameraRotation = 0.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public BrickEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

BrickEngine::Application* BrickEngine::CreateApplication()
{
	return new Sandbox();
}
