#pragma once

#include "BrickEngine/Window.h"
#include "BrickEngine/LayerStack.h"
#include "BrickEngine/Core.h"
#include "BrickEngine/Events/ApplicationEvent.h"

#include "BrickEngine/ImGui/ImGuiLayer.h"

#include "BrickEngine/Renderer/Shader.h"

#include "BrickEngine/Renderer/Buffer.h"

#include "BrickEngine/Renderer/VertexArray.h"

#include "BrickEngine/Renderer/OrthographicCamera.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
