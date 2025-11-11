#include "repch.h"
#include "Entity.h"

namespace RuiEngine {

	Entity::Entity(entt::entity entity, Scene* scene)
		: m_EntityHandle(entity), m_Scene(scene)
	{

	}

}