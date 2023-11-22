#include <NazaraEditor/Editor/UI/MainWindow.hpp>
#include <NazaraEditor/Editor/Application.hpp>

#include <NazaraEditor/Core/Components/CameraComponent.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "LOC_EDITOR_WINDOW_MAIN_TITLE", { "General", "Tools", "Plugins" })
	{
	}

	void MainWindow::OnRenderImgui()
	{
		Nz::EditorMainWindow::OnRenderImgui();

		if (ImGui::Begin("MainWindow"))
		{
			auto pos = ImGui::GetCursorPos();
			ImGui::Image(GetApplication()->GetEngineTexture());
			ImGui::SetCursorPos(pos); // everything else will be drawn on top of the texture

			auto cam = GetApplication()->GetMainCamera();
			auto& camcomponent = cam.get<Nz::EditorCameraComponent>();
			auto& transform = cam.get<Nz::NodeComponent>();

			auto desiredRotation = camcomponent.GetOrientation();
			auto rotation = transform.GetRotation().ToEulerAngles();
			
			ImGui::Text("Camera position: %.2f %.2f %.2f", transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
			ImGui::Text("Camera rotation: %.2f %.2f %.2f", rotation.roll.value, rotation.pitch.value, rotation.yaw.value);
			
			ImGui::End();
		}
	}
}