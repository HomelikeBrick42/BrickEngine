#include <BrickEngine.h>

class ExampleLayer : public BrickEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{

	}

	void OnEvent(BrickEngine::Event& event) override
	{
		
	}

};

class Sandbox : public BrickEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new BrickEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

BrickEngine::Application* BrickEngine::CreateApplication()
{
	return new Sandbox();
}
