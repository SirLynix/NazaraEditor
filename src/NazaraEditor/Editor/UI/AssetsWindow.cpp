#include <NazaraEditor/Editor/UI/AssetsWindow.hpp>

namespace NzEditor
{
	AssetsWindow::AssetsWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "LOC_EDITOR_WINDOW_ASSET_BROWSER_TITLE", { "Assets" })
	{
		BuildMenuBar();
	}

	void AssetsWindow::ImportAsset()
	{

	}

	void AssetsWindow::BuildMenuBar()
	{
		AddMenuAction({ "LOC_EDITOR_MENU_IMPORT" }, "Ctrl+I", [this]() { ImportAsset(); });
	}
}