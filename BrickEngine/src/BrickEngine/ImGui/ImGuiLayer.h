#pragma once

#include "BrickEngine/Layer.h"

#include "BrickEngine/Events/ApplicationEvent.h"
#include "BrickEngine/Events/MouseEvent.h"
#include "BrickEngine/Events/KeyEvent.h"

namespace BrickEngine {

	class BRICKENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
