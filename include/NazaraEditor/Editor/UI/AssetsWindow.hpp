#include <NazaraEditor/Core/UI/Window.hpp>

namespace Nz
{
	class EditorAssetsWindow
		: public Nz::EditorWindow
	{
	public:
		EditorAssetsWindow(EditorBaseApplication* app);

		void ImportAsset();

	protected:
		void BuildMenuBar();
	};
}
