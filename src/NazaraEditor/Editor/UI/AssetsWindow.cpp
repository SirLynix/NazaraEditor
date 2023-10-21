#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>

namespace NzEditor
{
	AssetsWindow::AssetsWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, Nz::LocalizedText("LOC_EDITOR_WINDOW_ASSET_BROWSER_TITLE"), { "Assets" })
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