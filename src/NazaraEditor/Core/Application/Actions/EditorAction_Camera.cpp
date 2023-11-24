#include <NazaraEditor/Core/Application/Actions/EditorAction_Camera.hpp>

#include <NazaraEditor/Core/Application/BaseApplication.hpp>

namespace Nz
{
	void RegisterCameraActions(EditorBaseApplication& app)
	{
		for (auto&& size : std::vector<Nz::Vector2ui>{
			{ 320, 340 }, { 640, 480 }, { 800, 600 }, { 1024, 768 },
			{ 1280, 720 }, { 1280, 960 }, { 1280, 1024 },
			{ 1366, 768 }, { 1440, 900 },
			{ 1920, 1080 },	{ 1920, 1200 },
			})
		{
			auto str = std::format("{} x {}", size.x, size.y);
			app.RegisterAction<Nz::EditorAction_SetCameraSize>({
				.className = std::format("{}_{}x{}", Nz::EditorAction_SetCameraSize::GetClassName(), size.x, size.y),
				.description = str.c_str(),
				.path = { "LOC_EDITOR_MENU_VIEW", "LOC_EDITOR_MENU_RESOLUTION", str.c_str()},
				.category = "Tools",
				}, size);
		}
	}

	void EditorAction_SetCameraSize::Execute()
	{
		Nz::EditorBaseApplication::Instance()->CreateEngineTexture(m_size);
	}
}