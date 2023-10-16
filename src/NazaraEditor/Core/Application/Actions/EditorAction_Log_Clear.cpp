#include <NazaraEditor/Core/Application/Actions/EditorAction_Log_Clear.hpp>
#include <NazaraEditor/Core/Application/EditorLogger.hpp>

namespace Nz
{
	void EditorAction_Log_Clear::Execute()
	{
		Nz::EditorLogger::Instance()->Clear();
	}
}