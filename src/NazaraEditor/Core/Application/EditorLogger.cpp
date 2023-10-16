#include <NazaraEditor/Core/Application/EditorLogger.hpp>

namespace Nz
{
	EditorLogger* EditorLogger::s_instance = nullptr;

	EditorLogger::EditorLogger()
	{
		NazaraAssert(s_instance == nullptr, "EditorLogger already exists");
		s_instance = this;

		Nz::Log::OnLogWrite.Connect([this](auto&& str) { m_text.emplace_back(str); });
		Nz::Log::OnLogWriteError.Connect([this](ErrorType, auto&& str, int, const char*, const char*) { m_text.emplace_back(str); });
	}

	EditorLogger::~EditorLogger()
	{
		s_instance = nullptr;
	}

	EditorLogger* EditorLogger::Instance()
	{
		return s_instance;
	}
}