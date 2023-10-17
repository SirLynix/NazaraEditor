#include <NazaraEditor/Editor/UI/MainWindow.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "MainWindow", { "General", "Plugins" })
	{
	}
}