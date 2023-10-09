#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>

namespace Nz
{
	EditorAssetsWindow::EditorAssetsWindow(EditorBaseApplication* app)
		: Nz::EditorWindow(app, "Assets Browser")
	{
		BuildMenuBar();
	}

	void EditorAssetsWindow::ImportAsset()
	{

	}

	void EditorAssetsWindow::BuildMenuBar()
	{
		AddMenuAction("Import", "Ctrl+I", [this]() { ImportAsset(); });
	}
}