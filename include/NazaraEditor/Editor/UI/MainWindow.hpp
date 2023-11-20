#include <NazaraEditor/Core/UI/MainWindow.hpp>

namespace NzEditor
{
	class MainWindow
		: public Nz::EditorMainWindow
	{
	public:
		MainWindow(Nz::EditorBaseApplication* app);

	protected:
		virtual void OnRenderImgui() override;
	};
}