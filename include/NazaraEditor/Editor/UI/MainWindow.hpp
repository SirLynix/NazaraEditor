#include <NazaraEditor/Core/UI/Window.hpp>

namespace Nz
{
	class EditorMainWindow
		: public Nz::EditorWindow
	{
	public:
		EditorMainWindow(EditorBaseApplication* app);

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