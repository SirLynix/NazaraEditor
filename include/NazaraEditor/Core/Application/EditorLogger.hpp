#pragma once

#include <NazaraEditor/Core/Core.hpp>
#include <Nazara/Core.hpp>

namespace Nz
{
	class NAZARAEDITOR_CORE_API EditorLogger
	{
	public:
		EditorLogger();
		virtual ~EditorLogger();

		static EditorLogger* Instance();

		void Clear() { m_text.clear(); }

		const std::vector<std::string>& GetLog() const { return m_text; }

	private:
		static EditorLogger* s_instance;
		std::vector<std::string> m_text;
	};
}