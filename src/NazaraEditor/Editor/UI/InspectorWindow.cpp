#include <NazaraEditor/Editor/UI/InspectorWindow.hpp>

#include <NazaraEditor/Editor/Application.hpp>

namespace NzEditor
{
	InspectorWindow::InspectorWindow(Nz::EditorBaseApplication* app)
		: Nz::EditorWindow(app, "Inspector")
	{
		app->OnEntitySelected.Connect(this, &InspectorWindow::OnEntitySelected);
	}

	void InspectorWindow::OnEditorGUI()
	{
		if (!m_currentEntity)
			return;

		Nz::EditorPropertyInspector<Nz::EditorRenderer> enumerator;
		enumerator.AddPropertyNoWrapper(m_currentEntity, "", "");
		ImGui::End();
	}

	void InspectorWindow::OnEntitySelected(entt::handle entity)
	{
		m_currentEntity = entity;
	}

	void InspectorWindow::OnEntityDeselected(entt::handle)
	{
		m_currentEntity = {};
	}
}