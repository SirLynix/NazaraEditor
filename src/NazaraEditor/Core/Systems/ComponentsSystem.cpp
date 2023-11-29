#include <NazaraEditor/Core/Systems/ComponentsSystem.hpp>
#include <NazaraEditor/Core/Components/CameraComponent.hpp>
#include <NazaraEditor/Core/Components/NameComponent.hpp>

#include <Nazara/Utility/Components/NodeComponent.hpp>

namespace Nz
{
	EditorComponentsSystem::EditorComponentsSystem(entt::registry& registry)
		: m_registry(registry)
		, m_cameraConstructObserver(registry, entt::collector.group<EditorCameraComponent, NodeComponent>())
		, m_entityConstructObserver(registry, entt::collector.group<EditorNameComponent, NodeComponent>())
	{
		m_cameraDestroyConnection = registry.on_destroy<EditorCameraComponent>().connect<&EditorComponentsSystem::OnCameraDestroy>(this);
		m_entityDestroyConnection = registry.on_destroy<EditorNameComponent>().connect<&EditorComponentsSystem::OnEntityDestroy>(this);
	}

	EditorComponentsSystem::~EditorComponentsSystem()
	{
		m_cameraConstructObserver.disconnect();
	}

	void EditorComponentsSystem::Update(Time elapsedTime)
	{
		m_cameraConstructObserver.each([&](entt::entity entity) {
			m_cameraEntities.insert(entity);
		});

		m_entityConstructObserver.each([&](entt::entity entity) {
			m_entities.insert(entity);
		});

		for (auto entity : m_cameraEntities)
		{
			EditorCameraComponent& camera = m_registry.get<EditorCameraComponent>(entity);
			NodeComponent& transform = m_registry.get<NodeComponent>(entity);

			camera.Update(elapsedTime, transform);
		}


		for (auto entity : m_entities)
		{
			EditorNameComponent& component = m_registry.get<EditorNameComponent>(entity);
			NodeComponent& transform = m_registry.get<NodeComponent>(entity);

			component.Update(elapsedTime, transform);
		}
	}

	void EditorComponentsSystem::OnCameraDestroy(entt::registry& registry, entt::entity entity)
	{
		m_cameraEntities.erase(entity);
	}

	void EditorComponentsSystem::OnEntityDestroy(entt::registry& registry, entt::entity entity)
	{
		m_entities.erase(entity);
	}
}