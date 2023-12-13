#include <NazaraEditor/Core/Application/Actions/EditorAction_Level.hpp>
#include <NazaraEditor/Core/Application/BaseApplication.hpp>
#include <NazaraEditor/Core/UI/PopupManager.hpp>

#include <Nazara/Graphics/Graphics.hpp>
#include <Nazara/Renderer/Texture.hpp>

namespace Nz
{
	void RegisterLevelActions(EditorBaseApplication& app)
	{
		Nz::TextureParams texParams;
		texParams.renderDevice = Nz::Graphics::Instance()->GetRenderDevice();
		texParams.loadFormat = Nz::PixelFormat::RGBA8_SRGB;

		app.RegisterAction<Nz::EditorAction_Level_New>({
				.description = "LOC_EDITOR_ACTION_LEVEL_NEW_DESC",
				.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_NEW" },
				.category = "General",
				.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::N, true, true),
				.icon = Nz::Texture::LoadFromFile("assets/editor/icons/file_new.png", texParams)
			});
		app.RegisterAction<Nz::EditorAction_Level_Open>({
				.description = "LOC_EDITOR_ACTION_LEVEL_OPEN_DESC",
				.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_OPEN" },
				.category = "General",
				.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::O, true, true),
				.icon = Nz::Texture::LoadFromFile("assets/editor/icons/file_open.png", texParams)
			});
		app.RegisterAction<Nz::EditorAction_Level_Save>({
				.description = "LOC_EDITOR_ACTION_LEVEL_SAVE_DESC",
				.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_SAVE" },
				.category = "General",
				.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::S, true, true),
				.icon = Nz::Texture::LoadFromFile("assets/editor/icons/file_save.png", texParams)
			});
	}

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