#include "repch.h"
#include "Scene.h"
#include "RuiEngine/Renderer/Renderer2D.h"
#include "Entity.h"

#include <glm/glm.hpp>

namespace RuiEngine {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstrcut(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		struct MeshComponent 
		{
			float Value;
			MeshComponent() = default;
		};
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4& transform)
				: Transform(transform) {}

			operator glm::mat4& () { return Transform; }
			operator const glm::mat4&() const { return Transform; }
		};

		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstrcut>();

		if(m_Registry.any_of<TransformComponent>(entity))
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			auto[transform, mesh] = m_Registry.get<TransformComponent, MeshComponent>(entity);
		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent, TransformComponent>);
		for (auto entity : group)
		{
			auto[transform, mesh] = m_Registry.get<TransformComponent,MeshComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name /*= std::string()*/)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Unkown Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}