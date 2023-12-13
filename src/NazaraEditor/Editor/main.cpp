
#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraImgui/NazaraImgui.hpp>
#include <NazaraEditor/Core.hpp>
#include <NazaraEditor/Core/Reflection.hpp>
#include <NazaraEditor/Core/Application/ApplicationComponent.hpp>

#include <NazaraEditor/Editor/Application.hpp>

NAZARA_REQUEST_DEDICATED_GPU()

#if 1
int main(int argc, char* argv[])
#else
int WinMain(int argc, char* argv[])
#endif
{
	// Logger must be created before app init to catch startup logs
	Nz::EditorLogger logger;

	Nz::Application<Nz::EditorCore> app(argc, argv);
	app.AddComponent<Nz::AppWindowingComponent>();
	app.AddComponent<Nz::AppFilesystemComponent>();
	app.AddComponent<Nz::AppEntitySystemComponent>();

	// Now that all required components are registered, boot up Editor
	auto& editor = app.AddComponent<Nz::EditorApplicationComponent>();
	editor.SetLogger(logger);
	app.AddComponent<NzEditor::Application>(editor);

	Nz::Localization::Instance()->LoadLocalizationFile(editor.GetResourceFolder() / "localization.csv");
	Nz::Localization::Instance()->SetLocale("en-US");

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

	editor.NewLevel();
	return app.Run();
}