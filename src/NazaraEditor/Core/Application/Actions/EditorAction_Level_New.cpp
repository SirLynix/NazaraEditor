#include <NazaraEditor/Core/Application/Actions/EditorAction_Level_New.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	void EditorAction_Level_New::Execute()
	{
		Nz::EditorBaseApplication::Instance()->NewLevel();
	}
}