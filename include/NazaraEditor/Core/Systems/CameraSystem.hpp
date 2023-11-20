#pragma once

#include <NazaraEditor/Core/Core.hpp>

#include <entt/entt.hpp>
#include <unordered_set>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorCameraSystem
	{
	public:
		static constexpr bool AllowConcurrent = false;
		static constexpr Int64 ExecutionOrder = 1'001;

		EditorCameraSystem(entt::registry& registry);
		~EditorCameraSystem();

		EditorCameraSystem(const EditorCameraSystem&) = delete;
		EditorCameraSystem& operator=(const EditorCameraSystem&) = delete;
		
		EditorCameraSystem(EditorCameraSystem&&) = delete;
		EditorCameraSystem& operator=(EditorCameraSystem&&) = delete;

		void Update(Time elapsedTime);

	private:
		void OnCameraDestroy(entt::registry& registry, entt::entity entity);

		entt::registry& m_registry;

		entt::observer m_cameraConstructObserver;
		entt::scoped_connection m_cameraDestroyConnection;

		std::unordered_set<entt::entity> m_cameraEntities;
	};
}