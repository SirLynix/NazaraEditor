#include <NazaraEditor/Editor/UI/MainWindow.hpp>

namespace NzEditor
{
	MainWindow::MainWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorMainWindow(app, "MainWindow")
	{
		BuildMenuBar();
	}

	void MainWindow::BuildMenuBar()
	{
		AddMenuAction("File|Project|New", "Ctrl+Shift+N", [this]() { NewProject(); });
		AddMenuAction("File|Project|Open", "Ctrl+Shift+O", [this]() { OpenProject(); });
		AddMenuAction("File|Project|Save", "Ctrl+Shift+S", [this]() { SaveProject(); });
		AddMenuAction("File|Level|New", "Ctrl+N", [this]() { NewLevel(); });
		AddMenuAction("File|Level|Open", "Ctrl+O", [this]() { OpenLevel(); });
		AddMenuAction("File|Level|Save", "Ctrl+S", [this]() { SaveLevel(); });
		AddMenuSeparator("File");
		AddMenuAction("File|Quit", "Ctrl+W", [this]() { Quit(); });
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