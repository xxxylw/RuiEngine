#pragma once

#include <entt.hpp>

#include "RuiEngine/Core/Timestep.h"

namespace RuiEngine {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
		void DestroyEntity(Entity entity);

		Entity CreateEntity(const std::string& tag = std::string());

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}