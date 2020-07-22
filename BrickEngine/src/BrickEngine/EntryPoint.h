#pragma once

#ifdef BRICKENGINE_PLATFORM_WINDOWS

extern BrickEngine::Application* BrickEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = BrickEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
