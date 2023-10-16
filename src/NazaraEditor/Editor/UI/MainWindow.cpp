#include <NazaraEditor/Editor/UI/MainWindow.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "MainWindow", { "General", "Plugins" })
	{
	}

	bool MainWindow::Quit()
	{
		return true;
	}

	bool MainWindow::NewLevel()
	{
		return true;
	}

	bool MainWindow::OpenLevel()
	{
		return true;
	}

	bool MainWindow::SaveLevel()
	{
		return true;
	}

	bool MainWindow::NewProject()
	{
		return true;
	}

	bool MainWindow::OpenProject()
	{
		return true;
	}

	bool MainWindow::SaveProject()
	{
		return true;
	}
}