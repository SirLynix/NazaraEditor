#include <NazaraEditor/Editor/UI/MainWindow.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "LOC_EDITOR_WINDOW_MAIN_TITLE", { "General", "Tools", "Plugins" })
	{
	}
}