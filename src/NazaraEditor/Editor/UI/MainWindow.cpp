#include <NazaraEditor/Editor/UI/MainWindow.hpp>
#include <NazaraEditor/Editor/Application.hpp>

#include <NazaraEditor/Core/Components/CameraComponent.hpp>

#include <Nazara/Core/Components/NodeComponent.hpp>

#include <NazaraImgui/ImguiWidgets.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "LOC_EDITOR_WINDOW_MAIN_TITLE", { "General", "Tools", "Plugins" })
	{
	}

	void MainWindow::OnRenderImgui()
	{
		Nz::EditorMainWindow::OnRenderImgui();

		if (ImGui::Begin("MainWindow", nullptr, ImGuiWindowFlags_NoScrollbar))
		{
			auto pos = ImGui::GetCursorPos();
			auto size = ImGui::GetContentRegionAvail();
			auto stretch = GetApplication()->GetEngineTextureStretchMode();

			auto texSize = GetApplication()->GetEngineTexture()->GetSize();
			
			if (stretch == Nz::StretchMode::KeepAspectRatio)
			{
				if (texSize.x > texSize.y)
				{
					float x = size.x;
					float y = texSize.y * size.x / texSize.x;
					ImGui::Image(GetApplication()->GetEngineTexture(), Nz::Vector2f{ x, y });
				}
				else
				{
					float x = texSize.x * size.y / texSize.y;
					float y = size.y;
					ImGui::Image(GetApplication()->GetEngineTexture(), Nz::Vector2f{ x, y });
				}
			}
			else
			{
				ImGui::Image(GetApplication()->GetEngineTexture(), Nz::Vector2f{ size.x, size.y });
			}
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