#pragma once

#include <entt.hpp>
#include "RuiEngine/Scene/Component.h"
#include "RuiEngine/Core/Timestep.h"

namespace RuiEngine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& tag = std::string());

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}