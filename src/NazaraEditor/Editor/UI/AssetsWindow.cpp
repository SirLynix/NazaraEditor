#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>

namespace NzEditor
{
	AssetsWindow::AssetsWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "Assets Browser")
	{
		BuildMenuBar();
	}

	void AssetsWindow::ImportAsset()
	{

	}

	void AssetsWindow::BuildMenuBar()
	{
		AddMenuAction("Import", "Ctrl+I", [this]() { ImportAsset(); });
	}
}