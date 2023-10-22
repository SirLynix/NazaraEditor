
#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraImgui/NazaraImgui.hpp>
#include <NazaraEditor/Core.hpp>

#include <NazaraEditor/Editor/Application.hpp>
#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>
#include <NazaraEditor/Editor/UI/InspectorWindow.hpp>
#include <NazaraEditor/Editor/UI/LevelWindow.hpp>
#include <NazaraEditor/Editor/UI/MainWindow.hpp>
#include <NazaraEditor/Editor/UI/OutputWindow.hpp>

NAZARA_REQUEST_DEDICATED_GPU()

#if 1
int main(int argc, char* argv[])
#else
int WinMain(int argc, char* argv[])
#endif
{
	NazaraUnused(argc);
	NazaraUnused(argv);

	Nz::EditorLogger logger;

	std::filesystem::path resourceDir = "assets/editor";
	if (!std::filesystem::is_directory(resourceDir) && std::filesystem::is_directory("../.." / resourceDir))
			resourceDir = "../.." / resourceDir;

	NzEditor::Application app;
	app.SetResourceFolder(resourceDir);
	app.SetLogger(logger);

	ImGui::EnsureContextOnThisThread();

	app.RegisterWindow<NzEditor::MainWindow>();
	app.RegisterWindow<NzEditor::AssetsWindow>();
	app.RegisterWindow<NzEditor::LevelWindow>();
	app.RegisterWindow<NzEditor::InspectorWindow>();
	app.RegisterWindow<NzEditor::OutputWindow>();

	Nz::Localization::Instance()->LoadLocalizationFile(resourceDir / "localization.csv");
	Nz::Localization::Instance()->SetLocale("en-US");

	Nz::TextureParams texParams;
	texParams.renderDevice = Nz::Graphics::Instance()->GetRenderDevice();
	texParams.loadFormat = Nz::PixelFormat::RGBA8_SRGB;

	app.RegisterAction<Nz::EditorAction_Level_New>({
			.description = "LOC_EDITOR_ACTION_LEVEL_NEW_DESC",
			.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_NEW" },
			.category = "General",
			.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::N, true, true),
			.icon = Nz::Texture::LoadFromFile(app.GetResourceFolder() / "icons" / "file_new.png", texParams)
		});
	app.RegisterAction<Nz::EditorAction_Level_Open>({
			.description = "LOC_EDITOR_ACTION_LEVEL_OPEN_DESC",
			.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_OPEN" },
			.category = "General",
			.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::O, true, true),
			.icon = Nz::Texture::LoadFromFile(app.GetResourceFolder() / "icons" / "file_open.png", texParams)
		});
	app.RegisterAction<Nz::EditorAction_Level_Save>({
			.description = "LOC_EDITOR_ACTION_LEVEL_SAVE_DESC",
			.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_LEVEL", "LOC_EDITOR_MENU_SAVE" },
			.category = "General",
			.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::S, true, true),
			.icon = Nz::Texture::LoadFromFile(app.GetResourceFolder() / "icons" / "file_save.png", texParams)
		});
	app.RegisterAction<Nz::EditorAction_Log_Clear>({
			.description = "LOC_EDITOR_ACTION_LOG_CLEAR_DESC",
			.path = { "LOC_EDITOR_MENU_LOG_CLEAR" },
			.category = "Output",
		});
	app.RegisterAction<Nz::EditorAction_Log_CopyToClipboard>({
			.description = "LOC_EDITOR_ACTION_LOG_COPY_DESC",
			.path = { "LOC_EDITOR_MENU_LOG_COPY" },
			.category = "Output",
		});
	app.RegisterAction<Nz::EditorAction_Quit>({
			.description = "LOC_EDITOR_ACTION_QUIT_DESC",
			.path = { "LOC_EDITOR_MENU_FILE", "LOC_EDITOR_MENU_QUIT" },
			.category = "General",
			.shortcut = Nz::Shortcut::Create(Nz::Keyboard::VKey::F4, false, false, true),
		});

	entt::meta<Nz::NodeComponent>()
		.type(entt::type_hash<Nz::NodeComponent>::value())
		.func<&Nz::ReflectComponent<Nz::EditorPropertyInspector<Nz::EditorRenderer>, Nz::NodeComponent>>(entt::hashed_string("Reflect"));
	entt::meta<Nz::CameraComponent>()
		.type(entt::type_hash<Nz::CameraComponent>::value())
		.func<&Nz::ReflectComponent<Nz::EditorPropertyInspector<Nz::EditorRenderer>, Nz::CameraComponent>>(entt::hashed_string("Reflect"));
	entt::meta<Nz::LightComponent>()
		.type(entt::type_hash<Nz::LightComponent>::value())
		.func<&Nz::ReflectComponent<Nz::EditorPropertyInspector<Nz::EditorRenderer>, Nz::LightComponent>>(entt::hashed_string("Reflect"));
	entt::meta<Nz::GraphicsComponent>()
		.type(entt::type_hash<Nz::GraphicsComponent>::value())
		.func<&Nz::ReflectComponent<Nz::EditorPropertyInspector<Nz::EditorRenderer>, Nz::GraphicsComponent>>(entt::hashed_string("Reflect"));
	entt::meta<Nz::EditorNameComponent>()
		.type(entt::type_hash<Nz::EditorNameComponent>::value())
		.func<&Nz::ReflectComponent<Nz::EditorPropertyInspector<Nz::EditorRenderer>, Nz::EditorNameComponent>>(entt::hashed_string("Reflect"));

	return app.Run();
}