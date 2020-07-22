#include "Application.h"

#include "BrickEngine/Events/ApplicationEvent.h"
#include "BrickEngine/Log.h"

namespace BrickEngine {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		BRICKENGINE_TRACE(e);

		while (true);
	}

}
