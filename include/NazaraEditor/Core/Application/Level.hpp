#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/EnttWorld.hpp>
#include <Nazara/Math/Ray.hpp>

namespace Nz
{
	class EditorBaseApplication;

	struct RaycastHit
	{
		entt::handle entity;

		Nz::Vector3f position;
		float distance;
	};

	class NAZARAEDITOR_CORE_API Level final
	{
	public:
		Level(EditorBaseApplication* app);

		inline bool IsValid() const { return m_world != nullptr; }

		inline Nz::EnttWorld* GetEnttWorld() { return m_world; }
		inline const Nz::EnttWorld* GetEnttWorld() const { return m_world; }

		entt::handle CreateEntity();
		bool CreateNewLevel();

		// This is slow af
		std::vector<RaycastHit> Raycast(const Nz::Rayf& ray);

	protected:
		EditorBaseApplication* m_application;

		Nz::EnttWorld* m_world;

		std::filesystem::path m_path;
		std::string m_name;
	};
}