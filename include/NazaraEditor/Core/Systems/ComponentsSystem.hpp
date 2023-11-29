#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/Time.hpp>

#include <entt/entt.hpp>
#include <unordered_set>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorComponentsSystem
	{
	public:
		static constexpr bool AllowConcurrent = false;
		static constexpr Int64 ExecutionOrder = 1'001;

		EditorComponentsSystem(entt::registry& registry);
		~EditorComponentsSystem();

		EditorComponentsSystem(const EditorComponentsSystem&) = delete;
		EditorComponentsSystem& operator=(const EditorComponentsSystem&) = delete;
		
		EditorComponentsSystem(EditorComponentsSystem&&) = delete;
		EditorComponentsSystem& operator=(EditorComponentsSystem&&) = delete;

		void Update(Time elapsedTime);

	private:
		void OnCameraDestroy(entt::registry& registry, entt::entity entity);
		void OnEntityDestroy(entt::registry& registry, entt::entity entity);

		entt::registry& m_registry;

		entt::observer m_cameraConstructObserver;
		entt::observer m_entityConstructObserver;
		entt::scoped_connection m_cameraDestroyConnection;
		entt::scoped_connection m_entityDestroyConnection;

		std::unordered_set<entt::entity> m_cameraEntities;
		std::unordered_set<entt::entity> m_entities;
	};
}