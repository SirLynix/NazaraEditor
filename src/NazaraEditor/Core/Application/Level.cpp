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

	std::vector<RaycastHit> Level::Raycast(const Nz::Rayf& ray)
	{
		std::vector<RaycastHit> entities;

		auto& registry = m_world->GetRegistry();
		for (auto&& entity : registry.storage<entt::entity>().each())
		{
			Nz::GraphicsComponent* component = registry.try_get<Nz::GraphicsComponent>(std::get<entt::entity>(entity));
			if (component != nullptr)
			{
				float distance = 0;
				if (ray.Intersect(component->GetAABB(), &distance))
				{
					entities.push_back({
						.entity = entt::handle(registry, std::get<entt::entity>(entity)),
						.position = ray.origin + ray.direction * distance,
						.distance = distance
					});
				}
			}
		}

		// sort the result by distance first
		std::sort(entities.begin(), entities.end(), [](auto&& A, auto&& B) { return A.distance < B.distance; });
		return entities;
	}
}