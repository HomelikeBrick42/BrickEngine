#include <BrickEngine.h>

class Sandbox : public BrickEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

BrickEngine::Application* BrickEngine::CreateApplication()
{
	return new Sandbox();
}