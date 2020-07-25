#include <BrickEngine.h>

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
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
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
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(new BrickEngine::Shader(vertexSrc, fragmentSrc));

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

		m_BlueShader.reset(new BrickEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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
		{
			BrickEngine::Renderer::Submit(m_BlueShader, m_SquareVA);

			BrickEngine::Renderer::Submit(m_Shader, m_VertexArray);
		}
		BrickEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(BrickEngine::Event& event) override
	{
	}
private:
	std::shared_ptr<BrickEngine::Shader> m_Shader;
	std::shared_ptr<BrickEngine::VertexArray> m_VertexArray;

	std::shared_ptr<BrickEngine::Shader> m_BlueShader;
	std::shared_ptr<BrickEngine::VertexArray> m_SquareVA;

	BrickEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraSpeed = 5.0f;
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
