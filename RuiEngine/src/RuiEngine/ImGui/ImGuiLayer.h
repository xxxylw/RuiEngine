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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvnets = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvnets = true;
		float m_Time = 0.0f;
	};
}