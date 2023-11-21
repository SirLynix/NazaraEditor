
#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>

#include <NazaraImgui/NazaraImgui.hpp>
#include <NazaraEditor/Core.hpp>

#include <NazaraEditor/Editor/Application.hpp>

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

	NzEditor::Application app;
	app.SetLogger(logger);

	ImGui::EnsureContextOnThisThread();

	Nz::Localization::Instance()->LoadLocalizationFile(app.GetResourceFolder() / "localization.csv");
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

	app.NewLevel();
	return app.Run();
}