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
		//BRICKENGINE_INFO("ExampleLayer::Update");
	}

	void OnEvent(BrickEngine::Event& event) override
	{
		BRICKENGINE_TRACE("{0}", event);
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
