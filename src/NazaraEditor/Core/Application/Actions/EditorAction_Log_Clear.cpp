#include <NazaraEditor/Core/Application/Actions/EditorAction_Log_Clear.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	void EditorAction_Log_Clear::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetLogger().Clear();
	}
}