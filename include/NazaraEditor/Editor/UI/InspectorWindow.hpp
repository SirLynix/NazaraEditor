#include <NazaraEditor/Core/UI/Window.hpp>

#include <entt/entt.hpp>

namespace Nz
{
	class EditorInspectorWindow
		: public Nz::EditorWindow
	{
	public:
		EditorInspectorWindow(EditorBaseApplication* app);

		virtual void OnEditorGUI() override;

	protected:
		void OnEntitySelected(entt::handle entity);
		void OnEntityDeselected(entt::handle);

		entt::handle m_currentEntity;
	};
}