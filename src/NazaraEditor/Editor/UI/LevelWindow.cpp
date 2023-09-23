#include <NazaraEditor/Editor/UI/LevelWindow.hpp>

#include <NazaraEditor/Editor/Application.hpp>

namespace Nz
{
	EditorLevelWindow::EditorLevelWindow()
		: Nz::EditorWindow("Level")
		, m_currentWorld(EditorApplication::Instance().GetCurrentWorld())
		, m_dirty(true)
	{
		EditorApplication::Instance().OnWorldChanged.Connect([this](Nz::EnttWorld* world) { m_currentWorld = world; m_dirty = true; });
		EditorApplication::Instance().OnEntityCreated.Connect([this](entt::handle) { m_dirty = true; });
		EditorApplication::Instance().OnEntityDestroyed.Connect([this](entt::handle) { m_dirty = true; });
		EditorApplication::Instance().OnEntityParentChanged.Connect([this](entt::handle) { m_dirty = true; });
	}

	void EditorLevelWindow::OnEditorGUI()
	{
		RefreshEntities();

		std::function<void(Nz::Node*)> drawHierarchy = [&](Nz::Node* c)
		{
			entt::handle entity = m_nodeToEntity[c];
			Nz::EditorImgui::Begin(entity, "", "");
			for (auto& child : c->GetChilds())
				drawHierarchy(child);
			Nz::EditorImgui::End(entity);
		};

		for (auto& node : m_rootNodes)
			drawHierarchy(node);
	}

	void EditorLevelWindow::RefreshEntities()
	{
		if (!m_dirty)
			return;

		m_dirty = false;
		m_rootNodes.clear();
		m_nodeToEntity.clear();

		if (m_currentWorld == nullptr)
			return;

		m_currentWorld->GetRegistry().each([&](const entt::entity entity) {
			entt::handle handle(m_currentWorld->GetRegistry(), entity);
			Nz::NodeComponent* component = handle.try_get<Nz::NodeComponent>();
			if (component != nullptr)
			{
				m_nodeToEntity[component] = handle;
				if (component->GetParent() == nullptr)
					m_rootNodes.push_back(component);
			}
		});
	}
}