#include <NazaraEditor/Core/UI/Window.hpp>

namespace NzEditor
{
	class AssetsWindow
		: public Nz::EditorWindow
	{
	public:
		AssetsWindow(Nz::EditorBaseApplication* app);

		void ImportAsset();

	protected:
		void BuildMenuBar();
	};
}
