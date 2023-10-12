#include <NazaraEditor/Editor/UI/LevelWindow.hpp>

#include <NazaraEditor/Editor/Application.hpp>

namespace NzEditor
{
	LevelWindow::LevelWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "Level")
		, m_currentLevel(app->GetLevel())
		, m_dirty(true)
	{
		app->OnWorldChanged.Connect([this](Nz::Level&) { m_dirty = true; });
		app->OnEntityCreated.Connect([this](entt::handle) { m_dirty = true; });
		app->OnEntityDestroyed.Connect([this](entt::handle) { m_dirty = true; });
		app->OnEntityParentChanged.Connect([this](entt::handle) { m_dirty = true; });
	}

	void LevelWindow::OnEditorGUI()
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

	void LevelWindow::RefreshEntities()
	{
		if (!m_dirty)
			return;

		m_dirty = false;
		m_rootNodes.clear();
		m_nodeToEntity.clear();

		if (!m_currentLevel.IsValid())
			return;

		auto& registry = m_currentLevel.GetEnttWorld()->GetRegistry();
		for(auto&& entity : registry.storage<entt::entity>().each())
		{
			entt::handle handle(registry, std::get<entt::entity>(entity));
			Nz::NodeComponent* component = handle.try_get<Nz::NodeComponent>();
			if (component != nullptr)
			{
				m_nodeToEntity[component] = handle;
				if (component->GetParent() == nullptr)
					m_rootNodes.push_back(component);
			}
		}
	}
}