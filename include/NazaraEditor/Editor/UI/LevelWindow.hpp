#include <NazaraEditor/Core.hpp>
#include <NazaraEditor/Core/UI/Window.hpp>

#include <Nazara/Core/Node.hpp>
#include <entt/entt.hpp>

namespace NzEditor
{
	class Level;

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