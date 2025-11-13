#pragma once

#include "RuiEngine/Core/Core.h"
#include "RuiEngine/Core/Log.h"
#include "RuiEngine/Scene/Scene.h"
#include "RuiEngine/Scene/Entity.h"

namespace RuiEngine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}