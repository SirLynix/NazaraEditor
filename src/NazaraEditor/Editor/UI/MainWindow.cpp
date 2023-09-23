#include <NazaraEditor/Editor/UI/MainWindow.hpp>

namespace Nz
{
	EditorMainWindow::EditorMainWindow()
		: Nz::EditorWindow("MainWindow")
	{
		BuildMenuBar();
	}

	void EditorMainWindow::BuildMenuBar()
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

	void EditorMainWindow::OnEditorGUI()
	{

	}

	bool EditorMainWindow::Quit()
	{
		return true;
	}

	bool EditorMainWindow::NewLevel()
	{
		return true;
	}

	bool EditorMainWindow::OpenLevel()
	{
		return true;
	}

	bool EditorMainWindow::SaveLevel()
	{
		return true;
	}

	bool EditorMainWindow::NewProject()
	{
		return true;
	}

	bool EditorMainWindow::OpenProject()
	{
		return true;
	}

	bool EditorMainWindow::SaveProject()
	{
		return true;
	}
}