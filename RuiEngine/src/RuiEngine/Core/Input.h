#pragma once

#include <glm/glm.hpp>

//#include "RuiEngine/Core/Core.h"
#include "RuiEngine/Core/KeyCodes.h"
#include "RuiEngine/Core/MouseCodes.h"

namespace RuiEngine {
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}