#include <NazaraEditor/Core/UI/Window.hpp>

#include <Nazara/Core.hpp>
#include <Nazara/Utility.hpp>

namespace Nz
{
	class EditorLevelWindow
		: public Nz::EditorWindow
	{
	public:
		EditorLevelWindow(EditorBaseApplication* app);

		virtual void OnEditorGUI() override;

	protected:
		void RefreshEntities();

		Nz::EnttWorld* m_currentWorld;
		bool m_dirty;

		std::vector<Nz::Node*> m_rootNodes;
		std::map<Nz::Node*, entt::handle> m_nodeToEntity;
	};
}