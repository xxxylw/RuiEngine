#pragma once

#include "RuiEngine/Layer.h"

namespace RuiEngine {

	class RE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;

	};
}