#pragma once

#include "BrickEngine/Window.h"
#include "BrickEngine/LayerStack.h"
#include "BrickEngine/Core.h"
#include "BrickEngine/Events/ApplicationEvent.h"

namespace BrickEngine {

	class BRICKENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
