#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <Nazara/Core/Clock.hpp>
#include <NazaraUtils/Signal.hpp>

#include <filesystem>
#include <memory>
#include <string>

namespace Nz
{
	class Billboard;
	class NodeComponent;
	class WorldInstance;

	enum EditorEntityFlags : uint64_t
	{
		EditorEntityFlags_None = 0,

		EditorEntityFlags_Hidden = 1 << 1,
	};

	class NAZARAEDITOR_CORE_API EditorNameComponent
	{
	public:
		EditorNameComponent() = default;
		EditorNameComponent(const EditorNameComponent&) = delete;
		EditorNameComponent(EditorNameComponent&&) = default;
		~EditorNameComponent() = default;

		EditorNameComponent& operator=(const EditorNameComponent&) = delete;
		EditorNameComponent& operator=(EditorNameComponent&&) = default;

		void Update(Time elapsedTime, NodeComponent& node);

		void SetName(const std::string& name) { m_name = name; }
		const std::string& GetName() const { return m_name; }

		void SetIcon(const std::filesystem::path& path);

		void SetFlags(const uint64_t flags) { m_flags = flags; }
		uint64_t GetFlags() const { return m_flags; }

		NazaraSignal(OnIconChanged, EditorNameComponent*, const std::filesystem::path& );

	private:

		std::string m_name;
		uint64_t m_flags;

		std::filesystem::path m_iconPath; // @TODO replace with asset

		struct BillboardData
		{
			size_t index;
			std::shared_ptr<Nz::WorldInstance> instance;
			std::shared_ptr<Nz::Billboard> billboard;
		};
		std::optional<BillboardData> m_icon;
	};

}