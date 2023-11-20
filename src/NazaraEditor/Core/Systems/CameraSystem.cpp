#include <NazaraEditor/Core/Systems/CameraSystem.hpp>
#include <NazaraEditor/Core/Components/CameraComponent.hpp>

#include <Nazara/Utility/Components/NodeComponent.hpp>

namespace Nz
{
	EditorCameraSystem::EditorCameraSystem(entt::registry& registry)
		: m_registry(registry)
		, m_cameraConstructObserver(registry, entt::collector.group<EditorCameraComponent, NodeComponent>())
	{
		m_cameraDestroyConnection = registry.on_destroy<EditorCameraComponent>().connect<&EditorCameraSystem::OnCameraDestroy>(this);
	}

	EditorCameraSystem::~EditorCameraSystem()
	{
		m_cameraConstructObserver.disconnect();
	}

	void EditorCameraSystem::Update(Time elapsedTime)
	{
		m_cameraConstructObserver.each([&](entt::entity entity) {
			m_cameraEntities.insert(entity);
		});

		for (auto entity : m_cameraEntities)
		{
			EditorCameraComponent& camera = m_registry.get<EditorCameraComponent>(entity);
			NodeComponent& transform = m_registry.get<NodeComponent>(entity);

			camera.Update(elapsedTime, transform);
		}
	}

	void EditorCameraSystem::OnCameraDestroy(entt::registry& registry, entt::entity entity)
	{
		m_cameraEntities.erase(entity);
	}
}