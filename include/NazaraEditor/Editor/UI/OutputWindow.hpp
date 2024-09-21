#include <NazaraEditor/Core.hpp>

#include <Nazara/Core.hpp>

namespace NzEditor
{
	class OutputWindow
		: public Nz::EditorWindow
	{
	public:
		OutputWindow(Nz::EditorBaseApplication* app);

		virtual void OnEditorGUI() override;

	protected:
		bool m_bScrollToBottom;
		bool m_bScrollToTop;
	};
}