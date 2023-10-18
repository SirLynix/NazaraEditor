#include <NazaraEditor/Core/Application/EditorLogger.hpp>

namespace Nz
{
	EditorLogger::EditorLogger()
	{
		Nz::Log::OnLogWrite.Connect([this](auto&& str) { m_text.emplace_back(str); });
		Nz::Log::OnLogWriteError.Connect([this](ErrorType, auto&& str, int, const char*, const char*) { m_text.emplace_back(str); });
	}
}