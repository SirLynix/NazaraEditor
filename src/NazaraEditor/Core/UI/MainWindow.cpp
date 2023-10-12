#include <NazaraEditor/Core/UI/MainWindow.h>

namespace Nz
{
	EditorMainWindow::EditorMainWindow(EditorBaseApplication* app, const std::string& name)
		: EditorWindow(app, name)
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