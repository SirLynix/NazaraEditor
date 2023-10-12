#pragma once

#include <NazaraEditor/Core/Config.hpp>

#include <string>

namespace Nz
{
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

		void SetName(const std::string& name) { m_name = name; }
		const std::string& GetName() const { return m_name; }

		void SetFlags(const uint64_t flags) { m_flags = flags; }
		uint64_t GetFlags() const { return m_flags; }

	private:
		std::string m_name;
		uint64_t m_flags;
	};
}