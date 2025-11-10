#pragma once

#include <entt.hpp>
#include "RuiEngine/Scene/Component.h"
#include "RuiEngine/Core/Timestep.h"

namespace RuiEngine {

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);

		entt::entity CreateEntity();

		// Temp
		entt::registry& Reg() { return m_Registry; }

	private:
		entt::registry m_Registry;
	};
}