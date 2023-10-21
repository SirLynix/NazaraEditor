#include <NazaraEditor/Core/Application/Actions/EditorAction_Level.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>

namespace Nz
{
	void EditorAction_Level_New::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetPopupManager().CreatePopup({
			.title = "LOC_EDITOR_POPUP_CREATE_LEVEL_TITLE",
			.description = "LOC_EDITOR_POPUP_CREATE_LEVEL_DESC",
			.choices = {
				{
					.name = "LOC_EDITOR_YES",
					.callback = []() { Nz::EditorBaseApplication::Instance()->NewLevel(); }
				},
				{
					.name = "LOC_EDITOR_NO"
				}
			}
			});
		
	}

	void EditorAction_Level_Open::Execute()
	{
		// TODO
	}

	void EditorAction_Level_Save::Execute()
	{
		// TODO
	}
}