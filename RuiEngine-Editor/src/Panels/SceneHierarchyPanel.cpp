#include "SceneHierarchyPanel.h"
#include "RuiEngine/Scene/Component.h"
#include <imgui/imgui.h>

namespace RuiEngine {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		// 这里我们要遍历所有entity，但是api不像Cherno那里写的了，得View<>，然后我又不想出现entt::entity，所以就view<TagComponent>，TagComponent是所有Entity都有的
		for (auto entityID : m_Context->m_Registry.view<TagComponent>())
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		}

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

}