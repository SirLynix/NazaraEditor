#pragma once

#include <NazaraEditor/Core/Core.hpp>
#include <Nazara/Core.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorLogger
	{
	public:
		EditorLogger();

		void Clear() { m_text.clear(); }

		const std::vector<std::string>& GetLog() const { return m_text; }

	private:
		EditorLogger(EditorLogger&) = delete;
		EditorLogger& operator=(const EditorLogger&) = delete;
		EditorLogger(EditorLogger&&) = delete;
		EditorLogger& operator=(EditorLogger&&) = delete;

		std::vector<std::string> m_text;
	};
}