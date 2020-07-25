#pragma once

#include "BrickEngine/Window.h"
#include "BrickEngine/LayerStack.h"
#include "BrickEngine/Core.h"
#include "BrickEngine/Events/ApplicationEvent.h"

#include "BrickEngine/ImGui/ImGuiLayer.h"

#include "BrickEngine/Renderer/Shader.h"

#include "BrickEngine/Renderer/Buffer.h"

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

		uint32_t m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}
