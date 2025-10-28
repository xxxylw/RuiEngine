#pragma once

#include "RuiEngine/Core/Layer.h"

#include "RuiEngine/Events/ApplicationEvent.h"
#include "RuiEngine/Events/KeyEvent.h"
#include "RuiEngine/Events/MouseEvent.h"

namespace RuiEngine {

	class RE_API ImGuiLayer : public Layer
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