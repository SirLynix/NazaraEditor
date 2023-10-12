#include <NazaraEditor/Core/Application/Level.hpp>

#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	Level::Level(EditorBaseApplication* app)
		: m_application(app)
		, m_world(nullptr)
	{}

	entt::handle Level::CreateEntity()
	{
		return m_world->CreateEntity();
	}

	bool Level::CreateNewLevel()
	{
		auto& ecs = m_application->GetComponent<Nz::AppEntitySystemComponent>();
		m_world = &ecs.AddWorld<Nz::EnttWorld>();
		return true;
	}
}