#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/EnttWorld.hpp>

namespace Nz
{
	class EditorBaseApplication;

	class NAZARAEDITOR_CORE_API Level final
	{
	public:
		Level(EditorBaseApplication* app);

		inline bool IsValid() const { return m_world != nullptr; }

		inline Nz::EnttWorld* GetEnttWorld() { return m_world; }
		inline const Nz::EnttWorld* GetEnttWorld() const { return m_world; }

		entt::handle CreateEntity();
		bool CreateNewLevel();

	protected:
		EditorBaseApplication* m_application;

		Nz::EnttWorld* m_world;

		std::filesystem::path m_path;
		std::string m_name;
	};
}