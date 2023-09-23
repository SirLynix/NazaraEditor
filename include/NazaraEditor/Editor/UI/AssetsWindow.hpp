#include <NazaraEditor/Core/UI/Window.hpp>

namespace Nz
{
	class EditorAssetsWindow
		: public Nz::EditorWindow
	{
	public:
		EditorAssetsWindow();

		void ImportAsset();

	protected:
		void BuildMenuBar();
	};
}
