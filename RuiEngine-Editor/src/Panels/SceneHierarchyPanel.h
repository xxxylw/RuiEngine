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

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}