#pragma once

#include "RuiEngine/Scene/Entity.h"

namespace RuiEngine {

	class ScriptableEntity
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}