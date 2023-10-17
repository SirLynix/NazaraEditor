#include <NazaraEditor/Core/UI/MainWindow.hpp>

namespace Nz
{
	EditorMainWindow::EditorMainWindow(EditorBaseApplication* app, const std::string& name, const std::vector<std::string>& categories)
		: EditorWindow(app, name, categories)
	{ }

	void EditorMainWindow::OnRenderImgui()
	{
		if (ImGui::BeginMainMenuBar())
		{
			DrawMenus();

			ImGui::EndMainMenuBar();
		}

		// Create docks everywhere in the main area
		ImGui::DockSpaceOverViewport();
	}
}