#include <NazaraEditor/Core/UI/MainWindow.h>

namespace NzEditor
{
	class MainWindow
		: public Nz::EditorMainWindow
	{
	public:
		MainWindow(Nz::EditorBaseApplication* app);

		bool Quit();

		bool NewLevel();
		bool OpenLevel();
		bool SaveLevel();

		bool NewProject();
		bool OpenProject();
		bool SaveProject();

	protected:
		void BuildMenuBar();
	};
}