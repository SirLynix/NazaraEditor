#include <NazaraEditor/Core/Application/Actions/EditorAction_Editor.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>
#include <NazaraLocalization/Localization.hpp>

namespace Nz
{
	void EditorAction_Quit::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetPopupManager().CreatePopup({
			.title = "Warning",
			.description = "Are you sure you want to exit? All unsaved work will be discarded",
			.choices = {
				{
					.name = "Yes",
					.callback = []() { Nz::EditorBaseApplication::Instance()->Quit(); }
				},
				{
					.name = "No"
				}
			}
			});

	}

	void EditorAction_SetLocale::Execute()
	{
		Nz::Localization::Instance()->SetLocale(m_locale);
	}
}