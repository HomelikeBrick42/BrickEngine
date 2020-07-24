#include <BrickEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public BrickEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	virtual void OnEvent(BrickEngine::Event& event) override
	{
		
	}

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
