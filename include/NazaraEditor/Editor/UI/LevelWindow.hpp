#include <NazaraEditor/Core.hpp>

#include <Nazara/Core.hpp>
#include <Nazara/Utility.hpp>

namespace NzEditor
{
	class LevelWindow
		: public Nz::EditorWindow
	{
	public:
		LevelWindow(Nz::EditorBaseApplication* app);

		virtual void OnEditorGUI() override;

	protected:
		void RefreshEntities();

		Nz::Level& m_currentLevel;
		bool m_dirty;

		std::vector<Nz::Node*> m_rootNodes;
		std::map<Nz::Node*, entt::handle> m_nodeToEntity;
	};
}