#include <NazaraEditor/Core/Application/Actions/EditorAction_Level_New.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>

namespace Nz
{
	void EditorAction_Level_New::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetPopupManager().CreatePopup({
			.title = "Warning",
			.description = "Are you sure you want to create a new level?",
			.choices = {
				{
					.name = "Yes",
					.callback = []() { Nz::EditorBaseApplication::Instance()->NewLevel(); }
				},
				{
					.name = "No"
				}
			}
			});
		
	}
}