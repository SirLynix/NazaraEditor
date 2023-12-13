#include <NazaraEditor/Core/Application/Actions/EditorAction_Editor.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>
#include <NazaraLocalization/Localization.hpp>

#include <Nazara/Core/ApplicationBase.hpp>

namespace Nz
{
	void RegisterEditorActions(EditorBaseApplication& app)
	{
		app.RegisterAction<Nz::EditorAction_Quit>({
				.description = "LOC_EDITOR_ACTION_QUIT_DESC",
				.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_QUIT" },
				.category = "General",
				.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::F4, false, false, true),
			});
	}

	void EditorAction_Quit::Execute()
	{
		Nz::EditorBaseApplication::Instance()->GetPopupManager().CreatePopup({
			.title = "Warning",
			.description = "Are you sure you want to exit? All unsaved work will be discarded",
			.choices = {
				{
					.name = "Yes",
					.callback = []() { Nz::ApplicationBase::Instance()->Quit(); }
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