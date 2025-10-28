#pragma once

#include "RuiEngine/Core/Input.h"
#include "RuiEngine/Core/Core.h"

namespace RuiEngine {
	
	class RE_API WindowsInput : public Input
	{
	protected:
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}